#![allow(unused)]
use crate::ir::typespace::{IrType, IrTypeSpace};
use std::collections::HashMap;

pub type TypeId = u32;
pub type ParameterId = usize;

#[derive(PartialEq, Debug, Clone)]
pub enum ValueLiteral {
    Null,
    True,
    False,
    I32(i32),
    I64(i64),
    U32(u32),
    U64(u64),
    F32(f32),
    F64(f64),
    Str(String),
}

#[derive(PartialEq, Debug, Clone)]
pub enum ValueFunction {
    Add,
    Sub,
    Div,
    Mul,
    Neg,
    Abs,
    Floor,
    Ceil,
    Round,
    And,
    Or,
    Not,
    Gt,
    Lt,
}

#[derive(PartialEq, Debug, Clone)]
pub enum ValueVariableBase {
    User,
    Current,
    Named(String),
}

#[derive(PartialEq, Debug, Clone)]
pub enum ValueStackItem {
    Function(ValueFunction),
    Literal(ValueLiteral),
    Variable(ValueVariableBase, Vec<IrType>, Vec<(String, Vec<IrType>)>),
}

pub type Value = Vec<ValueStackItem>;

#[derive(PartialEq, Debug, Clone)]
pub enum Filter {
    Is(TypeId),
    Eq(Value, Value),
    Lt(Value, Value),
    Gt(Value, Value),
}

#[derive(Debug, Clone)]
pub enum CompoundFilter {
    True,
    False,
    Conjunction(Vec<(bool, Filter)>),
}

pub enum FilterVector {
    /// Shorthand for Compound(CompoundFilter::True)
    True,
    /// Shorthand for Compound(CompoundFilter::False)
    False,
    /// A filter value that consists of multiple compound filters.
    /// The result is true if and only if one or more of the items is
    /// evaluated to true.
    Disjunction(Vec<CompoundFilter>),
}

pub type Selection = FilterVector;

pub struct Binding {
    property: Vec<(TypeId, String)>,
    value: Value,
}

pub struct CreateAction {
    base: TypeId,
    bindings: Vec<Binding>,
}

pub struct DeleteAction {
    selection: Selection,
}

pub struct UpdateAction {
    selection: Selection,
    bindings: Vec<Binding>,
}

pub enum SingleAction {
    Create(CreateAction),
    Delete(DeleteAction),
    Update(UpdateAction),
}

pub enum Reduce {
    Sum(Value, IrType),
    Min(Value, IrType),
    Max(Value, IrType),
    Avg(Value, IrType),
    Count(),
}

pub enum Map {
    Select(Value),
}

pub enum QueryLayer {
    Selection(Selection),
    Map(Map),
    Reduce(Reduce),
}

pub struct Query {
    name: String,
    parameters: Vec<(String, TypeId, bool)>, // name, type, nullable.
    guard: Selection,
    layers: Vec<QueryLayer>,
}

pub struct Action {
    name: String,
    parameters: Vec<(String, TypeId, bool)>, // name, type, nullable.
    guard: Selection,
    actions: Vec<SingleAction>,
}

pub struct Program {
    typespace: IrTypeSpace,
    queries: Vec<Query>,
    actions: Vec<Action>,
}

impl ValueStackItem {
    pub fn as_literal(self) -> ValueLiteral {
        match self {
            ValueStackItem::Literal(literal) => literal,
            _ => panic!("Value is not a literal."),
        }
    }
}

impl ValueLiteral {
    pub fn get_i128(&self) -> i128 {
        match self {
            ValueLiteral::I32(n) => *n as i128,
            ValueLiteral::I64(n) => *n as i128,
            ValueLiteral::U32(n) => *n as i128,
            ValueLiteral::U64(n) => *n as i128,
            _ => unimplemented!(),
        }
    }

    pub fn get_u64(&self) -> u64 {
        match self {
            ValueLiteral::I32(n) => *n as u64,
            ValueLiteral::I64(n) => *n as u64,
            ValueLiteral::U32(n) => *n as u64,
            ValueLiteral::U64(n) => *n as u64,
            _ => unimplemented!(),
        }
    }

    pub fn get_f64(&self) -> f64 {
        match self {
            ValueLiteral::I32(n) => *n as f64,
            ValueLiteral::I64(n) => *n as f64,
            ValueLiteral::U32(n) => *n as f64,
            ValueLiteral::U64(n) => *n as f64,
            ValueLiteral::F32(n) => *n as f64,
            ValueLiteral::F64(n) => *n as f64,
            _ => unimplemented!(),
        }
    }

    pub fn is_float(&self) -> bool {
        match self {
            ValueLiteral::F64(_) | ValueLiteral::F32(_) => true,
            _ => false,
        }
    }

    pub fn is_int(&self) -> bool {
        match self {
            ValueLiteral::I64(_) | ValueLiteral::I32(_) => true,
            _ => false,
        }
    }

    pub fn is_unsigned_int(&self) -> bool {
        match self {
            ValueLiteral::U64(_) | ValueLiteral::U32(_) => true,
            _ => false,
        }
    }
}

impl std::ops::Add<&ValueLiteral> for ValueLiteral {
    type Output = ValueLiteral;

    fn add(self, rhs: &ValueLiteral) -> ValueLiteral {
        match (
            self.is_float() || rhs.is_float(),
            self.is_unsigned_int() && self.is_unsigned_int(),
        ) {
            (true, _) => ValueLiteral::F64(self.get_f64() + rhs.get_f64()),
            (_, true) => ValueLiteral::U64(self.get_u64() + rhs.get_u64()),
            _ => ValueLiteral::I64((self.get_i128() + rhs.get_i128()) as i64),
        }
    }
}

impl std::ops::Sub<&ValueLiteral> for ValueLiteral {
    type Output = ValueLiteral;

    fn sub(self, rhs: &ValueLiteral) -> ValueLiteral {
        match self.is_float() || rhs.is_float() {
            true => ValueLiteral::F64(self.get_f64() - rhs.get_f64()),
            false => ValueLiteral::I64((self.get_i128() - rhs.get_i128()) as i64),
        }
    }
}

impl std::ops::Mul<&ValueLiteral> for ValueLiteral {
    type Output = ValueLiteral;

    fn mul(self, rhs: &ValueLiteral) -> ValueLiteral {
        match (
            self.is_float() || rhs.is_float(),
            self.is_unsigned_int() && self.is_unsigned_int(),
        ) {
            (true, _) => ValueLiteral::F64(self.get_f64() * rhs.get_f64()),
            (_, true) => ValueLiteral::U64(self.get_u64() * rhs.get_u64()),
            _ => ValueLiteral::I64((self.get_i128() + rhs.get_i128()) as i64),
        }
    }
}

impl std::ops::Div<&ValueLiteral> for ValueLiteral {
    type Output = ValueLiteral;

    fn div(self, rhs: &ValueLiteral) -> ValueLiteral {
        ValueLiteral::F64(self.get_f64() / rhs.get_f64())
    }
}

impl CompoundFilter {
    pub fn from_filter(filter: Filter, neg: bool) -> CompoundFilter {
        let mut parts = Vec::with_capacity(1);
        parts.push((neg, filter));
        CompoundFilter::Conjunction(parts)
    }

    pub fn neg(&self) -> CompoundFilter {
        match self {
            CompoundFilter::True => CompoundFilter::False,
            CompoundFilter::False => CompoundFilter::True,
            CompoundFilter::Conjunction(parts) => {
                let mut new_parts: Vec<(bool, Filter)> = Vec::with_capacity(parts.len());
                for (n, f) in parts {
                    new_parts.push((!n, f.clone()));
                }
                CompoundFilter::Conjunction(new_parts)
            }
        }
    }
}

impl FilterVector {
    pub fn from_filter(filter: Filter, neg: bool) -> FilterVector {
        let mut items = Vec::with_capacity(1);
        items.push(CompoundFilter::from_filter(filter, neg));
        FilterVector::Disjunction(items)
    }

    pub fn from_compound_filter(filter: CompoundFilter) -> FilterVector {
        match filter {
            CompoundFilter::True => FilterVector::True,
            CompoundFilter::False => FilterVector::False,
            _ => {
                let mut items = Vec::with_capacity(1);
                items.push(filter);
                FilterVector::Disjunction(items)
            }
        }
    }
}

impl std::ops::Add<CompoundFilter> for CompoundFilter {
    type Output = CompoundFilter;

    fn add(self, rhs: CompoundFilter) -> CompoundFilter {
        match (self, rhs) {
            (CompoundFilter::True, ret) => ret,
            (ret, CompoundFilter::True) => ret,
            (CompoundFilter::False, _) => CompoundFilter::False,
            (_, CompoundFilter::False) => CompoundFilter::False,
            (CompoundFilter::Conjunction(mut parts), CompoundFilter::Conjunction(rhs_parts)) => {
                for (neg, filter) in rhs_parts {
                    let mut found = false;

                    for (n, f) in &parts {
                        if filter == *f {
                            if neg != *n {
                                return CompoundFilter::False;
                            }

                            found = true;
                            break;
                        }
                    }

                    if !found {
                        parts.push((neg, filter));
                    }
                }

                CompoundFilter::Conjunction(parts)
            }
        }
    }
}

impl std::cmp::PartialEq for CompoundFilter {
    fn eq(&self, other: &CompoundFilter) -> bool {
        match (self, other) {
            (CompoundFilter::True, CompoundFilter::True) => true,
            (CompoundFilter::False, CompoundFilter::False) => true,
            (CompoundFilter::True, _) => false,
            (CompoundFilter::False, _) => false,
            (_, CompoundFilter::True) => false,
            (_, CompoundFilter::False) => false,
            (CompoundFilter::Conjunction(lhs), CompoundFilter::Conjunction(rhs)) => {
                if lhs.len() != rhs.len() {
                    return false;
                }

                let mut num_lhs_neg = 0;
                let mut num_rhs_neg = 0;
                for i in 0..lhs.len() {
                    if lhs[i].0 {
                        num_lhs_neg += 1;
                    }
                    if rhs[i].0 {
                        num_rhs_neg += 1;
                    }
                }
                if num_rhs_neg != num_rhs_neg {
                    return false;
                }

                for i in 0..lhs.len() {
                    let mut found = false;

                    for j in 0..rhs.len() {
                        if lhs[i] == rhs[j] {
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

impl std::ops::Add<CompoundFilter> for FilterVector {
    type Output = FilterVector;

    fn add(self, rhs: CompoundFilter) -> FilterVector {
        match (self, rhs) {
            (FilterVector::True, _) => FilterVector::True,
            (FilterVector::False, ret) => FilterVector::from_compound_filter(ret),
            (_, CompoundFilter::True) => FilterVector::True,
            (s, CompoundFilter::False) => s,
            (FilterVector::Disjunction(mut parts), current) => {
                let current_neg = current.neg();

                let mut found = false;
                for filter in &parts {
                    if current == *filter {
                        found = true;
                        break;
                    }

                    if current_neg == *filter {
                        return FilterVector::True;
                    }
                }
                if !found {
                    parts.push(current);
                }

                FilterVector::Disjunction(parts)
            }
        }
    }
}

impl std::ops::Add<FilterVector> for FilterVector {
    type Output = FilterVector;

    fn add(self, rhs: FilterVector) -> FilterVector {
        match (self, rhs) {
            (FilterVector::True, _) => FilterVector::True,
            (_, FilterVector::True) => FilterVector::True,
            (FilterVector::False, ret) => ret,
            (s, FilterVector::False) => s,
            (s, FilterVector::Disjunction(parts)) => {
                let mut result = s;

                for current in parts {
                    result = result + current;
                    match result {
                        FilterVector::True => break,
                        _ => {}
                    }
                }

                result
            }
        }
    }
}

impl std::ops::Mul<FilterVector> for FilterVector {
    type Output = FilterVector;

    fn mul(self, rhs: FilterVector) -> FilterVector {
        match (self, rhs) {
            /// [F] * [A, B] = [F + A, F + B] = [F, F] = [F]
            (FilterVector::False, _) => FilterVector::False,
            (_, FilterVector::False) => FilterVector::False,
            /// [T] * [A, B] = [T + A, T + B] = [A, B]
            (FilterVector::True, ret) => ret,
            (ret, FilterVector::True) => ret,
            (FilterVector::Disjunction(lhs), FilterVector::Disjunction(rhs)) => {
                let mut result = FilterVector::False;

                for a in &lhs {
                    for b in &rhs {
                        match a.clone() + b.clone() {
                            CompoundFilter::True => return FilterVector::True,
                            CompoundFilter::False => {}
                            x => result = result + x,
                        }
                    }
                }

                result
            }
        }
    }
}
