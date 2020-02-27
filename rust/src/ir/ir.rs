#![allow(unused)]
use crate::ir::typespace::{IrType, IrTypeSpace};
use std::collections::HashMap;

pub type TypeId = u32;
pub type ValueId = usize;
pub type ParameterId = usize;

#[derive(PartialEq, Debug)]
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

#[derive(PartialEq, Debug)]
pub enum ValueFunction {
    Add,
    Sub,
    Div,
    Mul,
    Pow,
    Gt,
    Lt,
    Gte,
    Lte,
    Neg,
    Floor,
    Ceil,
    Abs,
    And,
    Or,
    Not,
    Round,
}

#[derive(PartialEq, Debug)]
pub enum ValueVariableBase {
    User,
    Current,
    Named(String),
}

#[derive(PartialEq, Debug)]
pub enum ValueStackItem {
    Function(ValueFunction),
    Literal(ValueLiteral),
    Variable(ValueVariableBase, Vec<IrType>, Vec<(String, Vec<IrType>)>),
}

pub type Value = Vec<ValueStackItem>;

pub enum Filter {
    Is(TypeId),
    Eq(ValueId, ValueId),
    Lt(ValueId, ValueId),
    Gt(ValueId, ValueId),
}

pub struct Select {
    parts: Vec<(bool, Filter)>, // negated - the filter.
}

pub struct Selection {
    selects: Vec<Select>,
}

pub struct Binding {
    property: Vec<(TypeId, String)>,
    value: ValueId,
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
    Select(ValueId),
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
