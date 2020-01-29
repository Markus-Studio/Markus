#![allow(dead_code)]
use crate::parser::ast::*;
use crate::parser::diagnostics::Diagnostic;
use crate::parser::tokenizer::*;

pub struct Parser<'a> {
    tokenizer: Tokenizer<'a>,
    data: &'a Vec<u16>,
    tokens: Vec<Token>,
    current_token_index: usize,
    /// When parsing we sometimes want to store the parser state and
    /// be abel to restore to that state later on, for that we use
    /// store() and restore() methods, store pushes some data to this
    /// state history and restore() pops from this vector and sets the parser
    /// state back to this information.
    /// Type: (current_token_index, diagnostics.len())
    state_stack: Vec<(usize, usize)>,
    diagnostics: Vec<Diagnostic>,
}

impl<'a> Parser<'a> {
    pub fn new(data: &'a Vec<u16>, position: usize) -> Parser<'a> {
        Parser {
            tokenizer: Tokenizer::new(data, position),
            data: data,
            tokens: vec![],
            current_token_index: 0,
            state_stack: vec![(0, 0)],
            diagnostics: vec![],
        }
    }

    /// Consume the current token and move one token forward.
    #[inline]
    fn advance(&mut self, n: usize) {
        self.current_token_index += n;
    }

    /// Returns the n-th token from the current position, calling it with n = 0
    /// is equivalent of calling current as it returns the current token.
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

    /// Returns the current token.
    #[inline]
    fn current(&mut self) -> Option<Token> {
        self.lookahead(0)
    }

    #[inline]
    fn position(&mut self, n: usize) -> usize {
        match self.lookahead(n) {
            Some(token) => token.position.offset,
            None => {
                let index = self.current_token_index + n - 1;
                if index < self.tokens.len() {
                    self.tokens[index].position.offset + self.tokens[index].position.size
                } else {
                    self.tokenizer.position
                }
            }
        }
    }

    /// Pushes the current parser state into the state_stack.
    #[inline]
    fn store(&mut self) {
        self.state_stack
            .push((self.current_token_index, self.diagnostics.len()));
    }

    /// Restores the last previously stored state.
    #[inline]
    fn restore(&mut self) {
        let (token_index, diagnostics_len) = self.state_stack.pop().unwrap();
        self.current_token_index = token_index;
        self.diagnostics = self.diagnostics[0..diagnostics_len].to_vec();
    }

    /// Reports a diagnostic.
    #[inline]
    fn report(&mut self, diagnostic: Diagnostic) {
        self.diagnostics.push(diagnostic);
    }

    /// Expects the current token to be of the given kind, if so it consumes
    /// the current token and returns it otherwise reports an error and
    /// returns None.
    #[inline]
    fn expect(&mut self, kind: TokenKind) -> Option<Token> {
        match self.current() {
            Some(token) if token.kind == kind => {
                self.advance(1);
                Some(token)
            }
            _ => {
                // TODO(qti3e) Report error.
                None
            }
        }
    }

    /// Like `expect()` but does not report an error.
    #[inline]
    fn expect_optional(&mut self, kind: TokenKind) -> Option<Token> {
        match self.current() {
            Some(token) if token.kind == kind => {
                self.advance(1);
                Some(token)
            }
            _ => None,
        }
    }

    #[inline]
    fn collect_comma_separated<T, F: Fn(&mut Parser) -> Option<T>>(
        &mut self,
        vec: &mut Vec<T>,
        stops: Vec<TokenKind>,
        cb: F,
    ) {
        debug_assert!(stops.len() > 0);

        let mut expect_data = true;

        loop {
            match self.current() {
                Some(token) if stops.contains(&token.kind) => break,
                Some(token) if token.kind == TokenKind::Comma => {
                    if expect_data {
                        // TODO(qti3e) We expected data but found a comma so
                        // report an error.
                    }

                    self.advance(1);
                    expect_data = true;
                }
                Some(_) => {
                    if !expect_data {
                        // TODO(qti3e) We expected a comma so report an error.
                    }

                    match cb(self) {
                        Some(data) => {
                            vec.push(data);
                        }
                        None => {
                            self.advance(1);
                            // TODO(qti3e) Report error?
                        }
                    }

                    expect_data = false;
                }
                None => break,
            }
        }

        if expect_data {
            // TODO(qti3e) It means the last thing we've seen was a comma and
            // there wasn't any data after that so report an error.
        }
    }

    /// Try to parse an identifier from the token stream, consumes the token on
    /// success otherwise just returns None without changing the state.
    #[inline]
    fn parse_identifier(&mut self) -> Option<IdentifierNode> {
        match self.expect(TokenKind::Identifier) {
            Some(token) => Some(IdentifierNode {
                location: token.position,
            }),
            None => None,
        }
    }

    /// Parse a query declaration assuming that the `query` token is already
    /// seen but not consumed.
    #[inline]
    fn parse_query_declaration(&mut self) -> Option<QueryDeclarationNode> {
        debug_assert!(self
            .current()
            .unwrap()
            .compare_identifier(self.data, "query"));

        let start = self.position(0);
        self.advance(1);
        None
    }

    #[inline]
    fn parse_type_declaration(&mut self) -> Option<TypeDeclarationNode> {
        debug_assert!(self
            .current()
            .unwrap()
            .compare_identifier(self.data, "type"));

        let start = self.position(0);
        // Consume `type`.
        self.advance(1);

        let name = self.parse_identifier();
        let mut bases: Vec<IdentifierNode> = vec![];

        match self.expect_optional(TokenKind::Colon) {
            Some(_) => {
                self.collect_comma_separated(&mut bases, vec![TokenKind::LeftBrace], |parser| {
                    parser.parse_identifier()
                });
            }
            None => {}
        }

        self.expect(TokenKind::LeftBrace);
        // self.collect(&);
        self.expect(TokenKind::RightBrace);

        Some(TypeDeclarationNode {
            location: Span::from_positions(start, self.position(0)),
            name: name,
            bases: bases,
            fields: vec![],
        })
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
