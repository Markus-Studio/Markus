#![allow(unused)]
use crate::ir::typespace::{IrType, IrTypeSpace};
use std::collections::HashMap;

pub type TypeId = u32;
pub type FieldId = u32;
pub type ValueId = usize;
pub type ParameterId = usize;

pub enum LiteralValue {
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

pub enum Value {
    Current(Vec<IrType>),
    User(Vec<IrType>),
    Parameter(ParameterId),
    Literal(LiteralValue),
    Get(Box<Value>, FieldId, Vec<IrType>),
    Add(Box<Value>, Box<Value>, IrType),
    Sub(Box<Value>, Box<Value>, IrType),
    Mul(Box<Value>, Box<Value>, IrType),
    Div(Box<Value>, Box<Value>, IrType),
}

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
    property: Vec<(TypeId, FieldId)>,
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
    values: Vec<Value>,
    typespace: IrTypeSpace,
    queries: Vec<Query>,
    actions: Vec<Action>,
}
