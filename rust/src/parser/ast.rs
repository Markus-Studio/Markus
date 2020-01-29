#![allow(dead_code)]
use crate::parser::parser::Parser;
use crate::parser::source::Source;
use crate::parser::tokenizer::Span;

pub struct Program {
    pub source: Source,
    pub declarations: Vec<Declaration>,
}

#[derive(Debug)]
pub struct IdentifierNode {
    pub location: Span,
}

#[derive(Debug)]
pub struct IntLiteralNode {
    pub location: Span,
}

#[derive(Debug)]
pub struct FloatLiteralNode {
    pub location: Span,
}

#[derive(Debug)]
pub struct BooleanLiteralNode {
    pub location: Span,
}

#[derive(Debug)]
pub struct ParameterNode {
    pub location: Span,
    pub name: IdentifierNode,
    pub type_name: IdentifierNode,
}

#[derive(Debug)]
pub struct QueryDeclarationNode {
    pub location: Span,
    pub name: IdentifierNode,
    pub parameter: Vec<ParameterNode>,
    pub pipelines: Vec<CallNode>,
}

#[derive(Debug)]
pub struct TypeDeclarationNode {
    pub location: Span,
    pub name: Option<IdentifierNode>,
    pub bases: Vec<IdentifierNode>,
    pub fields: Vec<TypeFieldNode>,
}

#[derive(Debug)]
pub struct TypeFieldNode {
    pub location: Span,
    pub nullable: bool,
    pub name: IdentifierNode,
    pub type_name: IdentifierNode,
}

#[derive(Debug)]
pub struct CallNode {
    pub location: Span,
    pub callee_name: IdentifierNode,
    pub arguments: Vec<ValueNode>,
}

#[derive(Debug)]
pub struct AccessNode {
    pub location: Span,
    pub base: VariableReferenceNode,
    pub parts: Vec<IdentifierNode>,
}

#[derive(Debug)]
pub struct TypeReferenceNode {
    pub location: Span,
    pub name: IdentifierNode,
}

#[derive(Debug)]
pub enum Declaration {
    Query(QueryDeclarationNode),
    Type(TypeDeclarationNode),
}

#[derive(Debug)]
pub enum ValueNode {
    Access(AccessNode),
    Int(IntLiteralNode),
    Float(FloatLiteralNode),
    Boolean(BooleanLiteralNode),
    Call(CallNode),
    Type(TypeReferenceNode),
}

#[derive(Debug)]
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
        let mut parser = Parser::new(&self.source.content, 0);
        loop {
            match parser.parse_declaration() {
                Some(declaration) => {
                    self.declarations.push(declaration);
                }
                None => break,
            }
        }
    }
}
