use super::types::TypeRef;

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
    Variable(ValueVariableBase, TypeRef, Vec<(String, TypeRef)>),
}

pub type Value = Vec<ValueStackItem>;

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
