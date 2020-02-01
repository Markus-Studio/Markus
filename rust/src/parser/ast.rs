#![allow(dead_code)]
use crate::parser::tokenizer::Span;

#[derive(Debug, PartialEq)]
pub struct IdentifierNode {
    pub location: Span,
    pub value: String,
}

#[derive(Debug, PartialEq)]
pub struct IntLiteralNode {
    pub location: Span,
}

#[derive(Debug, PartialEq)]
pub struct FloatLiteralNode {
    pub location: Span,
}

#[derive(Debug, PartialEq)]
pub struct BooleanLiteralNode {
    pub location: Span,
}

#[derive(Debug, PartialEq)]
pub struct ParameterNode {
    pub location: Span,
    pub name: Option<IdentifierNode>,
    pub type_name: Option<IdentifierNode>,
}

#[derive(Debug, PartialEq)]
pub struct QueryDeclarationNode {
    pub location: Span,
    pub name: Option<IdentifierNode>,
    pub parameter: Vec<ParameterNode>,
    pub query: QueryNode,
}

#[derive(Debug, PartialEq)]
pub struct QueryNode {
    pub location: Span,
    pub pipelines: Vec<CallNode>,
}

#[derive(Debug, PartialEq)]
pub struct TypeDeclarationNode {
    pub location: Span,
    pub name: Option<IdentifierNode>,
    pub bases: Vec<IdentifierNode>,
    pub fields: Vec<TypeFieldNode>,
}

#[derive(Debug, PartialEq)]
pub struct TypeFieldNode {
    pub location: Span,
    pub nullable: bool,
    pub name: Option<IdentifierNode>,
    pub type_name: Option<IdentifierNode>,
}

#[derive(Debug, PartialEq)]
pub struct CallNode {
    pub location: Span,
    pub callee_name: Option<IdentifierNode>,
    pub arguments: Vec<ValueNode>,
}

#[derive(Debug, PartialEq)]
pub struct AccessNode {
    pub location: Span,
    pub base: VariableReferenceNode,
    pub parts: Vec<IdentifierNode>,
}

#[derive(Debug, PartialEq)]
pub struct TypeReferenceNode {
    pub location: Span,
    pub name: IdentifierNode,
}

#[derive(Debug, PartialEq)]
pub enum Declaration {
    Query(QueryDeclarationNode),
    Type(TypeDeclarationNode),
}

#[derive(Debug, PartialEq)]
pub enum ValueNode {
    Access(AccessNode),
    Int(IntLiteralNode),
    Float(FloatLiteralNode),
    Boolean(BooleanLiteralNode),
    Call(CallNode),
    Type(TypeReferenceNode),
}

#[derive(Debug, PartialEq)]
pub enum VariableReferenceNode {
    Current,
    Internal(IdentifierNode),
    Variable(IdentifierNode),
}

impl IdentifierNode {
    pub fn new(start: usize, value: &str) -> IdentifierNode {
        IdentifierNode {
            location: Span {
                offset: start,
                size: value.chars().count(),
            },
            value: String::from(value),
        }
    }
}
