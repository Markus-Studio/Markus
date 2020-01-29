#![allow(dead_code)]
use crate::parser::ast::*;
use crate::parser::tokenizer::*;

pub struct Parser<'a> {
    tokenizer: Tokenizer<'a>,
    data: &'a Vec<u16>,
    tokens: Vec<Token>,
    positions: Vec<usize>,
    current_token_index: usize,
    history_stack: Vec<usize>,
}

impl<'a> Parser<'a> {
    pub fn new(data: &'a Vec<u16>, position: usize) -> Parser<'a> {
        Parser {
            tokenizer: Tokenizer::new(data, position),
            data: data,
            tokens: vec![],
            positions: vec![],
            current_token_index: 0,
            history_stack: vec![0],
        }
    }

    /// Consume the current token and move one token forward.
    #[inline]
    fn advance(&mut self, n: usize) {
        self.current_token_index += n;
    }

    fn position(&mut self, n: usize) -> usize {
        self.lookahead(n);
        if self.positions.len() >= self.current_token_index + n {
            panic!("Out of range.");
        }
        self.positions[self.current_token_index + n]
    }

    #[inline]
    fn lookahead(&mut self, n: usize) -> Option<Token> {
        while self.current_token_index + n >= self.tokens.len() {
            let position = self.tokenizer.position;
            match self.tokenizer.next() {
                Some(token) => {
                    match token {
                        Token::Identifier { start, size: _ } => self.positions.push(start),
                        Token::Parameter { start, size: _ } => self.positions.push(start),
                        Token::InternalVariable { start, size: _ } => self.positions.push(start),
                        Token::Int { start, size: _ } => self.positions.push(start),
                        Token::Float { start, size: _ } => self.positions.push(start),
                        _ => self.positions.push(position),
                    }
                    self.tokens.push(token);
                }
                _ => return None,
            }
        }

        if self.current_token_index + n < self.tokens.len() {
            Some(self.tokens[self.current_token_index + n])
        } else {
            None
        }
    }

    #[inline]
    fn current(&mut self) -> Option<Token> {
        self.lookahead(0)
    }

    #[inline]
    fn store(&mut self) {
        self.history_stack.push(self.current_token_index);
    }

    #[inline]
    fn restore(&mut self) {
        self.current_token_index = self.history_stack.pop().unwrap();
    }

    /// Parse a query declaration assuming that the `query` token is already
    /// seen but not consumed.
    #[inline]
    fn parse_query_declaration(&mut self) -> Option<QueryDeclarationNode> {
        let start = self.position(0);
        self.advance(1);
        None
    }

    #[inline]
    fn parse_type_declaration(&mut self) -> Option<TypeDeclarationNode> {
        None
    }

    pub fn parse_declaration(&mut self) -> Option<Declaration> {
        match self.current() {
            Some(token) if token.compare_identifier(self.data, "query") => {
                match self.parse_query_declaration() {
                    Some(declaration) => Some(Declaration::Query(declaration)),
                    _ => None,
                }
            }
            Some(token) if token.compare_identifier(self.data, "type") => {
                match self.parse_type_declaration() {
                    Some(declaration) => Some(Declaration::Type(declaration)),
                    _ => None,
                }
            }
            _ => None,
        }
    }
}
