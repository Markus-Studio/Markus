#![allow(dead_code)]
use crate::parser::parser;
use crate::parser::source::Source;

pub struct Program {
    pub source: Source,
    pub declarations: Vec<Declaration>,
}

pub struct AstRange {
    pub offset: usize,
    pub size: usize,
}

pub struct IdentifierNode {
    pub range: AstRange,
}

pub struct IntLiteralNode {
    pub range: AstRange,
}

pub struct FloatLiteralNode {
    pub range: AstRange,
}

pub struct BooleanLiteralNode {
    pub range: AstRange,
}

pub struct ParameterNode {
    pub range: AstRange,
    pub name: IdentifierNode,
    pub type_name: IdentifierNode,
}

pub struct QueryDeclarationNode {
    pub range: AstRange,
    pub name: IdentifierNode,
    pub parameter: Vec<ParameterNode>,
    pub pipelines: Vec<CallNode>,
}

pub struct TypeDeclarationNode {
    pub range: AstRange,
    pub name: IdentifierNode,
    pub bases: Vec<IdentifierNode>,
    pub fields: Vec<TypeFieldNode>,
}

pub struct TypeFieldNode {
    pub range: AstRange,
    pub nullable: bool,
    pub name: IdentifierNode,
    pub type_name: IdentifierNode,
}

pub struct CallNode {
    pub range: AstRange,
    pub callee_name: IdentifierNode,
    pub arguments: Vec<ValueNode>,
}

pub struct AccessNode {
    pub range: AstRange,
    pub base: VariableReferenceNode,
    pub parts: Vec<IdentifierNode>,
}

pub struct TypeReferenceNode {
    pub range: AstRange,
    pub name: IdentifierNode,
}

pub enum Declaration {
    Query(QueryDeclarationNode),
    Type(TypeDeclarationNode),
}

pub enum ValueNode {
    Access(AccessNode),
    Int(IntLiteralNode),
    Float(FloatLiteralNode),
    Boolean(BooleanLiteralNode),
    Call(CallNode),
    Type(TypeReferenceNode),
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
    pub fn parse(&mut self) {
        self.declarations.clear();
    }
}
