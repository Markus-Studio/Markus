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

    fn parse_query_declaration(&mut self) -> Option<QueryDeclarationNode> {
        None
    }

    pub fn parse_declaration(&mut self) -> Option<Declaration> {
        match self.current() {
            Some(token) if token.compare_identifier(self.data, "query") => None,
            _ => None,
        }
    }
}
