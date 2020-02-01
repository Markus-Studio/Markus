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
    pub diagnostics: Vec<Diagnostic>,
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
    fn current_source_position(&mut self) -> usize {
        match self.current() {
            Some(token) => token.position.offset,
            None => {
                if self.current_token_index == 0 {
                    return 0;
                }

                let index = self.current_token_index - 1;
                if index < self.tokens.len() {
                    self.tokens[index].position.offset + self.tokens[index].position.size
                } else {
                    self.tokenizer.position
                }
            }
        }
    }

    #[inline]
    fn last_token_end_source_position(&self) -> usize {
        debug_assert!(self.current_token_index > 0);
        let index = self.current_token_index - 1;
        self.tokens[index].position.offset + self.tokens[index].position.size
    }

    #[inline]
    fn get_location(&self, start: usize) -> Span {
        Span::from_positions(start, self.last_token_end_source_position())
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
        self.diagnostics.truncate(diagnostics_len);
    }

    /// Reports a diagnostic.
    #[inline]
    fn report(&mut self, diagnostic: Diagnostic) {
        self.diagnostics.push(diagnostic);
    }

    /// Finds the first token of the given kind and returns the kind it does
    /// not consume the current token.
    #[inline]
    fn find_first_of(
        &mut self,
        kind: &Vec<TokenKind>,
        breaks: Vec<TokenKind>,
    ) -> Option<TokenKind> {
        debug_assert!(kind.len() > 0);
        match self.current() {
            Some(token) if kind.contains(&token.kind) => Some(token.kind),
            Some(token) => {
                self.report(Diagnostic::expect_one_of(token, kind));
                if breaks.contains(&token.kind) {
                    None
                } else {
                    self.advance(1);
                    self.find_first_of(kind, breaks)
                }
            }
            _ => {
                self.report(Diagnostic::early_end_of_file(
                    self.last_token_end_source_position(),
                ));
                None
            }
        }
    }

    /// Expects the current token to be of the given kind, if so it consumes
    /// the current token and returns it otherwise reports an error and returns
    /// `None` and also consumes the token if it's not in the `skip` vector.
    #[inline]
    fn expect(&mut self, kind: TokenKind, breaks: Vec<TokenKind>) -> Option<Token> {
        debug_assert!(!breaks.contains(&kind));
        match self.current() {
            Some(token) if token.kind == kind => {
                self.advance(1);
                Some(token)
            }
            Some(token) => {
                self.report(Diagnostic::expected_token(token, kind));
                if breaks.contains(&token.kind) {
                    None
                } else {
                    self.advance(1);
                    self.expect(kind, breaks)
                }
            }
            _ => {
                self.report(Diagnostic::early_end_of_file(
                    self.last_token_end_source_position(),
                ));
                None
            }
        }
    }

    /// Like `expect()` but does not report an error.
    #[inline]
    fn expect_optional(&mut self, kind: TokenKind, breaks: Vec<TokenKind>) -> Option<Token> {
        self.store();
        match self.expect(kind, breaks) {
            Some(token) => Some(token),
            None => {
                self.restore();
                None
            }
        }
    }

    #[inline]
    fn collect_separated_by<T, F: Fn(&mut Parser) -> Option<T>>(
        &mut self,
        result: &mut Vec<T>,
        stops: Vec<TokenKind>,
        cb: F,
        separator: TokenKind,
    ) {
        debug_assert!(stops.len() > 0);
        debug_assert!(!stops.contains(&separator));

        let mut expect_data = true;
        let mut last_comma: Option<Token> = None;

        loop {
            match self.current() {
                Some(token) if stops.contains(&token.kind) => break,
                Some(token) if token.kind == separator => {
                    if expect_data {
                        // We expected data but found a sep so report an error.
                        self.report(Diagnostic::unexpected_token(token));
                    }

                    last_comma = Some(token);
                    self.advance(1);
                    expect_data = true;
                }
                Some(token) => {
                    if !expect_data {
                        // We expected a comma so report an error.
                        self.report(Diagnostic::expected_token(token, separator));
                    }

                    match cb(self) {
                        Some(data) => {
                            result.push(data);
                        }
                        None => {
                            // We assume that cb() has already reported an error.
                            self.advance(1);
                        }
                    }

                    expect_data = false;
                }
                None => break,
            }
        }

        if expect_data {
            match last_comma {
                Some(token) => {
                    self.report(Diagnostic::unexpected_token(token));
                }
                _ => {}
            }
        }
    }

    #[inline]
    fn collect_comma_separated<T, F: Fn(&mut Parser) -> Option<T>>(
        &mut self,
        result: &mut Vec<T>,
        stops: Vec<TokenKind>,
        cb: F,
    ) {
        self.collect_separated_by(result, stops, cb, TokenKind::Comma)
    }

    #[inline]
    fn collect<T, F: Fn(&mut Parser) -> Option<T>>(
        &mut self,
        result: &mut Vec<T>,
        stops: Vec<TokenKind>,
        cb: F,
    ) {
        debug_assert!(stops.len() > 0);
        loop {
            match self.current() {
                Some(token) if stops.contains(&token.kind) => break,
                Some(_) => {
                    match cb(self) {
                        Some(data) => {
                            result.push(data);
                        }
                        None => {
                            // We assume that the error is already reported by
                            // `cb()`.
                            self.advance(1);
                        }
                    }
                }
                None => break,
            }
        }
    }

    #[inline]
    fn get_string_from_span(&self, span: Span) -> String {
        String::from_utf16(&self.data[span.offset..span.offset + span.size]).unwrap()
    }

    /// Try to parse an identifier from the token stream, consumes the token on
    /// success otherwise just returns None without changing the state.
    #[inline]
    fn parse_identifier(&mut self, skip: Vec<TokenKind>) -> Option<IdentifierNode> {
        match self.expect(TokenKind::Identifier, skip) {
            Some(token) => Some(IdentifierNode {
                location: token.position,
                value: self.get_string_from_span(token.position),
            }),
            None => None,
        }
    }

    /// Like parse_identifier but works on parameters.
    #[inline]
    fn parse_identifier_from_parameter(&mut self, skip: Vec<TokenKind>) -> Option<IdentifierNode> {
        match self.expect(TokenKind::Parameter, skip) {
            Some(token) => Some(IdentifierNode {
                location: token.position,
                value: self.get_string_from_span(token.position),
            }),
            None => None,
        }
    }

    /// Like parse_identifier but works on internal variables.
    #[inline]
    fn parse_identifier_from_internal_variable(
        &mut self,
        skip: Vec<TokenKind>,
    ) -> Option<IdentifierNode> {
        match self.expect(TokenKind::InternalVariable, skip) {
            Some(token) => Some(IdentifierNode {
                location: token.position,
                value: self.get_string_from_span(token.position),
            }),
            None => None,
        }
    }

    #[inline]
    fn parse_type_field(&mut self) -> Option<TypeFieldNode> {
        let start = self.current_source_position();

        let name = self.parse_identifier(vec![TokenKind::Question, TokenKind::Semicolon]);

        let nullable = match self.expect_optional(
            TokenKind::Question,
            vec![
                TokenKind::Colon,
                TokenKind::Semicolon,
                TokenKind::Identifier,
                TokenKind::RightBrace,
            ],
        ) {
            Some(_) => true,
            _ => false,
        };

        self.expect(
            TokenKind::Colon,
            vec![
                TokenKind::Semicolon,
                TokenKind::Identifier,
                TokenKind::RightBrace,
            ],
        );
        let type_name = self.parse_identifier(vec![TokenKind::Semicolon, TokenKind::RightBrace]);
        self.expect(
            TokenKind::Semicolon,
            vec![TokenKind::Identifier, TokenKind::RightBrace],
        );

        Some(TypeFieldNode {
            location: self.get_location(start),
            nullable: nullable,
            name: name,
            type_name: type_name,
        })
    }

    #[inline]
    fn parse_type_declaration(&mut self) -> Option<TypeDeclarationNode> {
        debug_assert!(self
            .current()
            .unwrap()
            .compare_identifier(self.data, "type"));

        let start = self.current_source_position();
        // Consume `type`.
        self.advance(1);

        let name = self.parse_identifier(vec![TokenKind::Colon, TokenKind::LeftBrace]);
        let mut bases: Vec<IdentifierNode> = vec![];
        let mut fields: Vec<TypeFieldNode> = vec![];

        match self.expect_optional(
            TokenKind::Colon,
            vec![TokenKind::LeftBrace, TokenKind::RightBrace],
        ) {
            Some(_) => {
                self.collect_comma_separated(&mut bases, vec![TokenKind::LeftBrace], |parser| {
                    parser.parse_identifier(vec![TokenKind::Comma])
                });
            }
            None => {}
        }

        self.expect(
            TokenKind::LeftBrace,
            vec![
                TokenKind::Identifier,
                TokenKind::Colon,
                TokenKind::RightBrace,
            ],
        );
        self.collect(&mut fields, vec![TokenKind::RightBrace], |parser| {
            parser.parse_type_field()
        });
        self.expect(TokenKind::RightBrace, vec![TokenKind::Identifier]);

        Some(TypeDeclarationNode {
            location: self.get_location(start),
            name: name,
            bases: bases,
            fields: fields,
        })
    }

    #[inline]
    fn parse_parameter(&mut self) -> Option<ParameterNode> {
        let start = self.current_source_position();
        let name = self.parse_identifier_from_parameter(vec![
            TokenKind::Colon,
            TokenKind::Identifier,
            TokenKind::Comma,
            TokenKind::RightParenthesis,
            TokenKind::LeftBrace,
            TokenKind::RightBrace,
        ]);

        self.expect(
            TokenKind::Colon,
            vec![
                TokenKind::Identifier,
                TokenKind::Comma,
                TokenKind::RightParenthesis,
                TokenKind::LeftBrace,
                TokenKind::RightBrace,
            ],
        );

        let type_name = self.parse_identifier(vec![
            TokenKind::Parameter,
            TokenKind::Comma,
            TokenKind::RightParenthesis,
            TokenKind::LeftBrace,
            TokenKind::RightBrace,
        ]);

        Some(ParameterNode {
            location: self.get_location(start),
            name: name,
            type_name: type_name,
        })
    }

    #[inline]
    fn consume_int_literal(&mut self) -> IntLiteralNode {
        let token = self.current().unwrap();
        debug_assert_eq!(token.kind, TokenKind::Int);
        self.advance(1);
        IntLiteralNode {
            location: token.position,
        }
    }

    #[inline]
    fn consume_float_literal(&mut self) -> FloatLiteralNode {
        let token = self.current().unwrap();
        debug_assert_eq!(token.kind, TokenKind::Float);
        self.advance(1);
        FloatLiteralNode {
            location: token.position,
        }
    }

    #[inline]
    fn consume_boolean_literal(&mut self) -> BooleanLiteralNode {
        let token = self.current().unwrap();
        debug_assert_eq!(token.kind, TokenKind::Boolean);
        self.advance(1);
        BooleanLiteralNode {
            location: token.position,
        }
    }

    #[inline]
    fn consume_variable_reference(&mut self) -> VariableReferenceNode {
        let token = self.current().unwrap();
        match token.kind {
            TokenKind::Dot => VariableReferenceNode::Current,
            TokenKind::Parameter => VariableReferenceNode::Variable(
                self.parse_identifier_from_parameter(vec![]).unwrap(),
            ),
            TokenKind::InternalVariable => VariableReferenceNode::Internal(
                self.parse_identifier_from_internal_variable(vec![])
                    .unwrap(),
            ),
            _ => panic!("Unexpected token passed to consume_variable_reference()."),
        }
    }

    #[inline]
    fn consume_access(&mut self) -> AccessNode {
        let start = self.current_source_position();
        let base = self.consume_variable_reference();
        let mut parts: Vec<IdentifierNode> = vec![];
        let mut read_parts = true;

        self.store();
        match self.find_first_of(
            &vec![TokenKind::Dot, TokenKind::Identifier],
            vec![
                TokenKind::Comma,
                TokenKind::RightParenthesis,
                TokenKind::Parameter,
                TokenKind::InternalVariable,
                TokenKind::Boolean,
                TokenKind::Int,
                TokenKind::Float,
            ],
        ) {
            Some(TokenKind::Dot) => {
                self.advance(1);
            }
            Some(TokenKind::Identifier) => {
                let token = self.current().unwrap();
                self.report(Diagnostic::expected_token(token, TokenKind::Dot));
            }
            _ => {
                self.restore();
                read_parts = false;
            }
        }

        if read_parts {
            self.collect_separated_by(
                &mut parts,
                vec![
                    TokenKind::Comma,
                    TokenKind::RightParenthesis,
                    TokenKind::Parameter,
                    TokenKind::InternalVariable,
                    TokenKind::Boolean,
                    TokenKind::Int,
                    TokenKind::Float,
                ],
                |parser| {
                    parser.parse_identifier(vec![
                        TokenKind::Dot,
                        TokenKind::Comma,
                        TokenKind::RightParenthesis,
                        TokenKind::Parameter,
                        TokenKind::InternalVariable,
                        TokenKind::Boolean,
                        TokenKind::Int,
                        TokenKind::Float,
                    ])
                },
                TokenKind::Dot,
            );
        }

        AccessNode {
            location: self.get_location(start),
            base: base,
            parts: parts,
        }
    }

    #[inline]
    fn consume_type_reference(&mut self) -> TypeReferenceNode {
        let token = self.current().unwrap();
        debug_assert_eq!(token.kind, TokenKind::Identifier);
        self.advance(1);
        TypeReferenceNode {
            location: token.position,
            name: IdentifierNode {
                location: token.position,
                value: self.get_string_from_span(token.position),
            },
        }
    }

    #[inline]
    fn consume_type_reference_or_call(&mut self) -> ValueNode {
        let token = self.current().unwrap();
        debug_assert_eq!(token.kind, TokenKind::Identifier);
        let current_index = self.current_token_index;
        self.advance(1);

        match self.expect_optional(
            TokenKind::LeftParenthesis,
            vec![
                TokenKind::RightBrace,
                TokenKind::RightParenthesis,
                TokenKind::Comma,
            ],
        ) {
            Some(_) => {
                self.current_token_index = current_index;
                ValueNode::Call(self.parse_call().unwrap())
            }
            None => {
                self.current_token_index = current_index;
                ValueNode::Type(self.consume_type_reference())
            }
        }
    }

    #[inline]
    fn parse_value(&mut self) -> Option<ValueNode> {
        match self.find_first_of(
            &vec![
                TokenKind::Dot,
                TokenKind::Identifier,
                TokenKind::LeftParenthesis,
                TokenKind::Parameter,
                TokenKind::InternalVariable,
                TokenKind::Boolean,
                TokenKind::Int,
                TokenKind::Float,
            ],
            vec![
                TokenKind::Comma,
                TokenKind::RightBrace,
                TokenKind::RightParenthesis,
            ],
        ) {
            Some(TokenKind::Int) => Some(ValueNode::Int(self.consume_int_literal())),
            Some(TokenKind::Float) => Some(ValueNode::Float(self.consume_float_literal())),
            Some(TokenKind::Boolean) => Some(ValueNode::Boolean(self.consume_boolean_literal())),
            Some(TokenKind::Dot)
            | Some(TokenKind::Parameter)
            | Some(TokenKind::InternalVariable) => Some(ValueNode::Access(self.consume_access())),
            Some(TokenKind::LeftParenthesis) => Some(ValueNode::Call(self.parse_call().unwrap())),
            Some(TokenKind::Identifier) => Some(self.consume_type_reference_or_call()),
            _ => None,
        }
    }

    #[inline]
    fn parse_call(&mut self) -> Option<CallNode> {
        let start = self.current_source_position();
        let mut arguments: Vec<ValueNode> = vec![];

        let name = self.parse_identifier(vec![
            TokenKind::LeftParenthesis,
            TokenKind::RightParenthesis,
            TokenKind::Comma,
            TokenKind::RightBrace,
            //
            TokenKind::Int,
            TokenKind::Float,
            TokenKind::Parameter,
            TokenKind::InternalVariable,
            TokenKind::Dot,
        ]);

        self.expect(
            TokenKind::LeftParenthesis,
            vec![
                TokenKind::RightParenthesis,
                TokenKind::Comma,
                TokenKind::RightBrace,
                //
                TokenKind::Identifier,
                TokenKind::Int,
                TokenKind::Float,
                TokenKind::Parameter,
                TokenKind::InternalVariable,
                TokenKind::Dot,
            ],
        );

        self.collect_comma_separated(
            &mut arguments,
            vec![TokenKind::LeftBrace, TokenKind::RightParenthesis],
            |parser| parser.parse_value(),
        );

        self.expect(
            TokenKind::RightParenthesis,
            vec![
                TokenKind::Comma,
                TokenKind::RightBrace,
                TokenKind::Identifier,
                TokenKind::Int,
                TokenKind::Float,
                TokenKind::Parameter,
                TokenKind::InternalVariable,
                TokenKind::Dot,
            ],
        );

        Some(CallNode {
            location: self.get_location(start),
            callee_name: name,
            arguments: arguments,
        })
    }

    #[inline]
    fn parse_query(&mut self) -> QueryNode {
        let start = self.current_source_position();
        let mut pipelines: Vec<CallNode> = vec![];

        self.expect(
            TokenKind::LeftBrace,
            vec![TokenKind::Identifier, TokenKind::LeftParenthesis],
        );

        self.collect_comma_separated(&mut pipelines, vec![TokenKind::RightBrace], |parser| {
            parser.parse_call()
        });

        self.expect(TokenKind::RightBrace, vec![TokenKind::Identifier]);

        QueryNode {
            location: self.get_location(start),
            pipelines: pipelines,
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

        let start = self.current_source_position();
        self.advance(1);

        let name = self.parse_identifier(vec![TokenKind::LeftParenthesis, TokenKind::LeftBrace]);
        let mut parameters: Vec<ParameterNode> = vec![];

        self.expect(
            TokenKind::LeftParenthesis,
            vec![
                TokenKind::Parameter,
                TokenKind::Colon,
                TokenKind::Identifier,
                TokenKind::Comma,
                TokenKind::RightParenthesis,
                TokenKind::LeftBrace,
                TokenKind::RightBrace,
            ],
        );

        self.collect_comma_separated(
            &mut parameters,
            vec![TokenKind::LeftBrace, TokenKind::RightParenthesis],
            |parser| parser.parse_parameter(),
        );

        self.expect(
            TokenKind::RightParenthesis,
            vec![
                TokenKind::LeftBrace,
                TokenKind::RightBrace,
                TokenKind::Identifier,
                TokenKind::LeftParenthesis,
            ],
        );

        let query = self.parse_query();

        Some(QueryDeclarationNode {
            location: self.get_location(start),
            name: name,
            parameter: parameters,
            query: query,
        })
    }

    pub fn parse_declaration(&mut self) -> Option<Declaration> {
        match self.current() {
            Some(token) if token.compare_identifier(self.data, "type") => {
                match self.parse_type_declaration() {
                    Some(declaration) => Some(Declaration::Type(declaration)),
                    _ => None,
                }
            }
            Some(token) if token.compare_identifier(self.data, "query") => {
                match self.parse_query_declaration() {
                    Some(declaration) => Some(Declaration::Query(declaration)),
                    _ => None,
                }
            }
            _ => None,
        }
    }
}
