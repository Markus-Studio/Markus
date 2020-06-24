use super::types::TypeRef;
use super::value::Value;

#[derive(PartialEq, Debug, Clone)]
pub enum AtomicFilter {
    Is(TypeRef),
    Eq(Value, Value),
    Lt(Value, Value),
    Gt(Value, Value),
    TestVariable(usize),
}

#[derive(Debug, Clone)]
pub enum Conjunction {
    True,
    False,
    Conjunction(Vec<(bool, AtomicFilter)>),
}

#[derive(Debug, Clone)]
pub enum Disjunction {
    /// Shorthand for Disjunction(CompoundFilter::True)
    True,
    /// Shorthand for Disjunction(CompoundFilter::False)
    False,
    /// A filter value that consists of multiple compound filters.
    /// The result is true if and only if one or more than one of the
    /// items evaluates to true.
    Disjunction(Vec<Conjunction>),
}

pub type Selection = Disjunction;

impl Conjunction {
    pub fn from_filter(filter: AtomicFilter, neg: bool) -> Conjunction {
        let mut parts = Vec::with_capacity(1);
        parts.push((neg, filter));
        Conjunction::Conjunction(parts)
    }

    pub fn reverse(self) -> Conjunction {
        match self {
            Conjunction::True => Conjunction::False,
            Conjunction::False => Conjunction::True,
            Conjunction::Conjunction(parts) => {
                let mut new_parts: Vec<(bool, AtomicFilter)> = Vec::with_capacity(parts.len());
                for (n, f) in parts {
                    new_parts.push((!n, f));
                }
                Conjunction::Conjunction(new_parts)
            }
        }
    }

    pub fn split(self) -> Disjunction {
        match self {
            Conjunction::True => Disjunction::True,
            Conjunction::False => Disjunction::False,
            Conjunction::Conjunction(parts) => {
                let mut result = Disjunction::False;

                for (neg, filter) in parts {
                    let compound = Conjunction::from_filter(filter, neg);
                    result = result + compound;
                }

                result
            }
        }
    }

    pub fn is_superset_of(&self, other: &Conjunction) -> bool {
        match (self, other) {
            (Conjunction::Conjunction(self_members), Conjunction::Conjunction(other_members)) => {
                if other_members.len() > self_members.len() {
                    return false;
                }

                for (neg, filter) in other_members {
                    let mut found = false;

                    for (n, f) in self_members {
                        if n == neg && filter == f {
                            found = true;
                            break;
                        }
                    }

                    if !found {
                        return false;
                    }
                }

                true
            }
            (Conjunction::True, Conjunction::True) | (Conjunction::False, Conjunction::False) => {
                true
            }
            _ => false,
        }
    }
}

impl Disjunction {
    pub fn from_filter(filter: AtomicFilter, neg: bool) -> Disjunction {
        let mut items = Vec::with_capacity(1);
        items.push(Conjunction::from_filter(filter, neg));
        Disjunction::Disjunction(items)
    }

    pub fn from_compound_filter(filter: Conjunction) -> Disjunction {
        match filter {
            Conjunction::True => Disjunction::True,
            Conjunction::False => Disjunction::False,
            _ => {
                let mut items = Vec::with_capacity(1);
                items.push(filter);
                Disjunction::Disjunction(items)
            }
        }
    }

    pub fn is_true(&self) -> bool {
        match self {
            Disjunction::True => true,
            _ => false,
        }
    }

    pub fn is_false(&self) -> bool {
        match self {
            Disjunction::False => true,
            _ => false,
        }
    }
}

impl std::ops::Add<Conjunction> for Conjunction {
    type Output = Conjunction;

    fn add(self, rhs: Conjunction) -> Conjunction {
        match (self, rhs) {
            (Conjunction::True, ret) => ret,
            (ret, Conjunction::True) => ret,
            (Conjunction::False, _) => Conjunction::False,
            (_, Conjunction::False) => Conjunction::False,
            (Conjunction::Conjunction(mut self_members), Conjunction::Conjunction(rhs_members)) => {
                for (neg, filter) in rhs_members {
                    let mut found = false;

                    for (n, f) in &self_members {
                        if filter == *f {
                            if neg != *n {
                                return Conjunction::False;
                            }

                            found = true;
                            break;
                        }
                    }

                    if !found {
                        self_members.push((neg, filter));
                    }
                }

                Conjunction::Conjunction(self_members)
            }
        }
    }
}

impl std::cmp::PartialEq for Conjunction {
    fn eq(&self, other: &Conjunction) -> bool {
        match (self, other) {
            (Conjunction::True, Conjunction::True) => true,
            (Conjunction::False, Conjunction::False) => true,
            (Conjunction::True, _) => false,
            (Conjunction::False, _) => false,
            (_, Conjunction::True) => false,
            (_, Conjunction::False) => false,
            (Conjunction::Conjunction(self_members), Conjunction::Conjunction(other_members)) => {
                if self_members.len() != other_members.len() {
                    return false;
                }

                let mut num_lhs_neg = 0;
                let mut num_rhs_neg = 0;
                for i in 0..self_members.len() {
                    if self_members[i].0 {
                        num_lhs_neg += 1;
                    }
                    if other_members[i].0 {
                        num_rhs_neg += 1;
                    }
                }
                if num_rhs_neg != num_rhs_neg {
                    return false;
                }

                for i in 0..self_members.len() {
                    let mut found = false;

                    for j in 0..other_members.len() {
                        if self_members[i] == other_members[j] {
                            found = true;
                            break;
                        }
                    }

                    if !found {
                        return false;
                    }
                }

                true
            }
        }
    }
}

impl std::ops::Add<Conjunction> for Disjunction {
    type Output = Disjunction;

    fn add(self, rhs: Conjunction) -> Disjunction {
        match (self, rhs) {
            (Disjunction::True, _) => Disjunction::True,
            (Disjunction::False, ret) => Disjunction::from_compound_filter(ret),
            (_, Conjunction::True) => Disjunction::True,
            (s, Conjunction::False) => s,
            (Disjunction::Disjunction(mut parts), current) => {
                let mut found = false;
                for filter in &parts {
                    if filter.is_superset_of(&current) {
                        found = true;
                        break;
                    }
                }
                if found {
                    return Disjunction::Disjunction(parts);
                }

                let clone = current.clone();
                let negated = current.reverse().split();
                if let Disjunction::Disjunction(members) = negated {
                    for member in members {
                        for filter in &parts {
                            if *filter == member {
                                return Disjunction::True;
                            }
                        }
                    }
                }

                parts.push(clone);
                Disjunction::Disjunction(parts)
            }
        }
    }
}

impl std::ops::Add<Disjunction> for Disjunction {
    type Output = Disjunction;

    fn add(self, rhs: Disjunction) -> Disjunction {
        match (self, rhs) {
            (Disjunction::True, _) => Disjunction::True,
            (_, Disjunction::True) => Disjunction::True,
            (Disjunction::False, ret) => ret,
            (s, Disjunction::False) => s,
            (s, Disjunction::Disjunction(parts)) => {
                let mut result = s;

                for current in parts {
                    result = result + current;
                    if result.is_true() {
                        break;
                    }
                }

                result
            }
        }
    }
}

impl std::ops::Mul<Disjunction> for Disjunction {
    type Output = Disjunction;

    fn mul(self, rhs: Disjunction) -> Disjunction {
        match (self, rhs) {
            /// [F] * [A, B] = [F + A, F + B] = [F, F] = [F]
            (Disjunction::False, _) => Disjunction::False,
            (_, Disjunction::False) => Disjunction::False,
            /// [T] * [A, B] = [T + A, T + B] = [A, B]
            (Disjunction::True, ret) => ret,
            (ret, Disjunction::True) => ret,
            (Disjunction::Disjunction(self_members), Disjunction::Disjunction(other_members)) => {
                let mut result = Disjunction::False;

                for a in &self_members {
                    for b in &other_members {
                        match a.clone() + b.clone() {
                            Conjunction::True => return Disjunction::True,
                            Conjunction::False => {}
                            x => result = result + x,
                        }
                    }
                }

                result
            }
        }
    }
}

impl std::ops::Neg for Disjunction {
    type Output = Disjunction;

    fn neg(self) -> Self::Output {
        match self {
            Disjunction::True => Disjunction::False,
            Disjunction::False => Disjunction::True,
            Disjunction::Disjunction(parts) => {
                if parts.len() == 0 {
                    return Disjunction::False;
                }

                let mut result = Disjunction::True;

                for filter in parts {
                    result = result * filter.reverse().split();
                    if result.is_true() {
                        break;
                    }
                }

                result
            }
        }
    }
}
