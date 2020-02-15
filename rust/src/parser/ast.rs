#![allow(dead_code)]
use crate::parser::tokenizer::Span;
use std::rc::Rc;

#[derive(Debug, PartialEq)]
pub enum Declaration {
    Query(Rc<QueryDeclarationNode>),
    Type(Rc<TypeDeclarationNode>),
    Action(Rc<ActionDeclarationNode>),
}

#[derive(Debug, PartialEq)]
pub struct IdentifierNode {
    pub location: Span,
    pub value: String,
}

#[derive(Debug, PartialEq)]
pub struct IntLiteralNode {
    pub location: Span,
    pub neg: bool,
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
pub struct ActionDeclarationNode {
    pub location: Span,
    pub name: Option<IdentifierNode>,
    pub parameters: Vec<ParameterNode>,
    pub statements: Vec<ActionStatement>,
}

#[derive(Debug, PartialEq)]
pub struct PropertyBindingNode {
    pub location: Span,
    pub bindings: Vec<FieldBindingNode>,
}

#[derive(Debug, PartialEq)]
pub struct FieldBindingNode {
    pub location: Span,
    pub uri: Vec<IdentifierNode>,
    pub value: Option<BindingValueNode>,
}

#[derive(Debug, PartialEq)]
pub enum BindingValueNode {
    Access(AccessNode),
    Int(IntLiteralNode),
    Float(FloatLiteralNode),
    Boolean(BooleanLiteralNode),
    Call(CallNode),
    Create(Option<IdentifierNode>, Option<PropertyBindingNode>),
}

#[derive(Debug, PartialEq)]
pub enum ActionStatement {
    Validate(QueryNode),
    Create(Option<IdentifierNode>, Option<PropertyBindingNode>),
    Update(Option<ActionValueReference>, Option<PropertyBindingNode>),
    Delete(Option<ActionValueReference>),
}

#[derive(Debug, PartialEq)]
pub enum ActionValueReference {
    Query(QueryNode),
    Internal(IdentifierNode),
    Variable(IdentifierNode),
}

#[derive(Debug, PartialEq)]
pub enum ValueNode {
    Access(AccessNode),
    Int(IntLiteralNode),
    Float(FloatLiteralNode),
    Boolean(BooleanLiteralNode),
    Call(CallNode),
    Type(TypeReferenceNode),
    Query(QueryNode),
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

impl ValueNode {
    pub fn get_location(&self) -> Span {
        match self {
            ValueNode::Access(value) => value.location,
            ValueNode::Boolean(value) => value.location,
            ValueNode::Call(value) => value.location,
            ValueNode::Float(value) => value.location,
            ValueNode::Int(value) => value.location,
            ValueNode::Query(value) => value.location,
            ValueNode::Type(value) => value.location,
        }
    }
}
