#![allow(dead_code)]
use crate::parser::ast::*;
use crate::parser::tokenizer::*;

pub struct Parser<'a> {
    tokenizer: Tokenizer<'a>,
    data: &'a Vec<u16>,
    tokens: Vec<Token>,
    current_token_index: usize,
    history_stack: Vec<usize>,
}

impl<'a> Parser<'a> {
    pub fn new(data: &'a Vec<u16>, position: usize) -> Parser<'a> {
        Parser {
            tokenizer: Tokenizer::new(data, position),
            data: data,
            tokens: vec![],
            current_token_index: 0,
            history_stack: vec![0],
        }
    }

    /// Consume the current token and move one token forward.
    #[inline]
    fn advance(&mut self, n: usize) {
        self.current_token_index += n;
    }

    #[inline]
    fn position(&mut self, n: usize) -> usize {
        match self.lookahead(n) {
            Some(token) => token.position.start,
            None => {
                panic!("Out of range.");
            }
        }
    }

    #[inline]
    fn lookahead(&mut self, n: usize) -> Option<Token> {
        while self.current_token_index + n >= self.tokens.len() {
            match self.tokenizer.next() {
                Some(token) => {
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
