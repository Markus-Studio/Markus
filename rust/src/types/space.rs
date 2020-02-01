use crate::parser::ast::TypeDeclarationNode;
use std::collections::HashMap;

pub type TypeId = u32;

struct BaseGraphEdge {
    object: TypeId,
    parent: TypeId,
}

pub struct Space {
    type_names: HashMap<String, TypeId>,
    last_type_id: TypeId,
    base_graph: Vec<BaseGraphEdge>,
    types: Vec<TypeDeclarationNode>,
}
