#![allow(dead_code)]
use crate::parser::ast::{IntLiteralNode, QueryDeclarationNode, QueryNode, ValueNode};
use crate::program::{MarkusType, TypeSpace};
use std::collections::HashMap;

struct QueryValidatorContext<'a> {
    space: &'a TypeSpace,
    branches: Vec<Vec<MarkusType>>,
    current: Vec<MarkusType>,
    variables: HashMap<String, MarkusType>,
}

impl<'a> QueryValidatorContext<'a> {
    #[inline]
    pub fn branch_in(&mut self) {
        self.branches.push(Vec::new());
    }

    #[inline]
    pub fn branch_out(&mut self) {
        let types = self.branches.pop().unwrap();
        if types.len() > 0 {
            let union = MarkusType::create_union_from(types);
            self.set_current(union);
        }
    }

    #[inline]
    pub fn path_enter(&mut self) {
        let current_type = self.get_current().clone();
        self.current.push(current_type);
    }

    #[inline]
    pub fn path_exit(&mut self) {
        self.branches
            .last_mut()
            .unwrap()
            .push(self.current.pop().unwrap());
    }

    #[inline]
    pub fn set_current(&mut self, current: MarkusType) {
        let last_index = self.current.len() - 1;
        self.current[last_index] = current;
    }

    #[inline]
    pub fn get_current(&self) -> &MarkusType {
        self.current.last().unwrap()
    }

    #[inline]
    pub fn resolve_variable(&self, name: &str) -> Option<&MarkusType> {
        self.variables.get(name)
    }
}

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
    pub fn verify<'a>(space: &'a TypeSpace) {
        let context = QueryValidatorContext {
            space: space,
            branches: Vec::new(),
            current: vec![space.get_query_input_type()],
            variables: HashMap::new(),
        };
    }
}
