#![allow(dead_code)]
use crate::parser::source::{Range, Source};

pub struct Program {
    source: Source,
    declarations: Vec<Declaration>,
}

pub struct IdentifierNode {
    range: Range,
}

pub struct IntLiteralNode {
    range: Range,
}

pub struct FloatLiteralNode {
    range: Range,
}

pub struct BooleanLiteralNode {
    range: Range,
}

pub struct NumericLiteral {
    range: Range,
}

pub struct ParameterNode {
    range: Range,
    name: IdentifierNode,
    type_name: IdentifierNode,
}

pub struct QueryDeclarationNode {
    range: Range,
    name: IdentifierNode,
    parameter: Vec<ParameterNode>,
    pipelines: Vec<CallNode>,
}

pub struct CallNode {
    range: Range,
    callee_name: IdentifierNode,
    arguments: Vec<ValueNode>,
}

pub struct AccessNode {
    range: Range,
    base: VariableReferenceNode,
    parts: Vec<IdentifierNode>,
}

pub enum Declaration {
    Query(QueryDeclarationNode),
}

pub enum Literal {
    Int(IntLiteralNode),
    Float(FloatLiteralNode),
    Boolean(BooleanLiteralNode),
}

pub enum ValueNode {
    Access(AccessNode),
    Literal(Literal),
    Call(CallNode),
}

pub enum VariableReferenceNode {
    Current,
    Internal(IdentifierNode),
    Variable(IdentifierNode),
}

impl Program {
    /// Constructs a new program from the given source file, but it does not
    /// parse the data, you should call .parse() after the construction.
    pub fn new(source: Source) -> Program {
        Program {
            source: source,
            declarations: vec![],
        }
    }

    /// Hard parse the source code.
    pub fn parse() {}
}
