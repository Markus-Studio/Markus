use crate::parser::ast::{IntLiteralNode, QueryDeclarationNode, ValueNode};
use crate::program::{MarkusType, TypeSpace};

struct QueryContext {}

impl ValueNode {
    /// Computes and returns type of this value.
    pub fn get_type(&self, space: &TypeSpace) -> Option<MarkusType> {
        match self {
            ValueNode::Int(IntLiteralNode { neg, .. }) => {
                if *neg {
                    Some(space.resolve_type("%neg-int").unwrap().clone())
                } else {
                    Some(space.resolve_type("%int").unwrap().clone())
                }
            }
            ValueNode::Float(_) => Some(space.resolve_type("%float").unwrap().clone()),
            ValueNode::Boolean(_) => Some(space.resolve_type("bool").unwrap().clone()),
            _ => panic!("Not implemented."),
        }
    }
}

impl QueryDeclarationNode {
    pub fn verify() {}
}
