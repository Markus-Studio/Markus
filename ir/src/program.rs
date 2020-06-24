#![allow(unused)]
use super::sat::*;
use super::types::*;
use super::value::*;
use common::bimap::BiMap;
use std::collections::HashMap;

pub struct Binding {
    property: Vec<(TypeRef, String)>,
    value: Value,
}

pub struct CreateAction {
    base: TypeRef,
    bindings: Vec<Binding>,
}

pub struct DeleteAction {
    target: Selection,
}

pub struct UpdateAction {
    target: Selection,
    bindings: Vec<Binding>,
}

pub enum SingleAction {
    Create(CreateAction),
    Delete(DeleteAction),
    Update(UpdateAction),
}

pub enum Reduce {
    Sum(Value, TypeRef),
    Min(Value, TypeRef),
    Max(Value, TypeRef),
    Avg(Value, TypeRef),
    Group(Value, TypeRef, Option<Box<QueryLayer>>),
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

pub struct Parameter {
    pub name: String,
    pub ir_type: TypeRef,
    pub optional: bool,
}

pub struct Query {
    name: String,
    parameters: Vec<Parameter>,
    guard: Selection,
    layers: Vec<QueryLayer>,
}

pub struct Action {
    name: String,
    parameters: Vec<Parameter>, // name, type, nullable.
    guard: Selection,
    actions: Vec<SingleAction>,
}

pub struct Program {
    typespace: TypeSpace,
    queries: Vec<Query>,
    actions: Vec<Action>,
}
