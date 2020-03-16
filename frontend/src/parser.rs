use crate::ast::*;
use crate::diagnostics::Diagnostic;
use crate::tokenizer::*;
use std::rc::Rc;

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
            data,
            tokens: vec![],
            current_token_index: 0,
            state_stack: vec![(0, 0)],
            diagnostics: vec![],
        }
    }

    /// Consume the current token and move one token forward.
    #[inline(always)]
    fn advance(&mut self, n: usize) {
        self.current_token_index += n;
    }

    /// Returns the n-th token from the current position, calling it with n = 0
    /// is equivalent of calling current as it returns the current token.
    #[inline(always)]
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
    #[inline(always)]
    fn current(&mut self) -> Option<Token> {
        self.lookahead(0)
    }

    #[inline(always)]
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

    #[inline(always)]
    fn last_token_end_source_position(&self) -> usize {
        debug_assert!(self.current_token_index > 0);
        let index = self.current_token_index - 1;
        if index < self.tokens.len() {
            self.tokens[index].position.offset + self.tokens[index].position.size
        } else {
            let index = self.tokens.len() - 1;
            self.tokens[index].position.offset + self.tokens[index].position.size
        }
    }

    #[inline(always)]
    fn get_location(&self, start: usize) -> Span {
        Span::from_positions(start, self.last_token_end_source_position())
    }

    /// Pushes the current parser state into the state_stack.
    #[inline(always)]
    fn store(&mut self) {
        self.state_stack
            .push((self.current_token_index, self.diagnostics.len()));
    }

    /// Restores the last previously stored state.
    #[inline(always)]
    fn restore(&mut self) {
        let (token_index, diagnostics_len) = self.state_stack.pop().unwrap();
        self.current_token_index = token_index;
        self.diagnostics.truncate(diagnostics_len);
    }

    /// Reports a diagnostic.
    #[inline(always)]
    fn report(&mut self, diagnostic: Diagnostic) {
        self.diagnostics.push(diagnostic);
    }

    /// Finds the first token of the given kind and returns the kind it does
    /// not consume the current token.
    #[inline(always)]
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
    #[inline(always)]
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
            None => {
                self.report(Diagnostic::early_end_of_file(
                    self.last_token_end_source_position(),
                ));
                None
            }
        }
    }

    /// Like `expect()` but does not report an error.
    #[inline(always)]
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

    #[inline(always)]
    fn collect_separated_by<T, F: Fn(&mut Parser) -> Option<T>>(
        &mut self,
        result: &mut Vec<T>,
        stops: Vec<TokenKind>,
        cb: F,
        separator: TokenKind,
        allow_trailing_separator: bool,
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

        if expect_data && !allow_trailing_separator {
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
        allow_trailing_separator: bool,
    ) {
        self.collect_separated_by(
            result,
            stops,
            cb,
            TokenKind::Comma,
            allow_trailing_separator,
        )
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
    fn parse_type_field(&mut self) -> TypeFieldNode {
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

        TypeFieldNode {
            location: self.get_location(start),
            nullable,
            name,
            type_name,
        }
    }

    #[inline]
    fn parse_type_declaration(&mut self) -> TypeDeclarationNode {
        debug_assert!(self.current().unwrap().kind == TokenKind::TypeKeyword);

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
                self.collect_comma_separated(
                    &mut bases,
                    vec![TokenKind::LeftBrace],
                    |parser| parser.parse_identifier(vec![TokenKind::Comma]),
                    false,
                );
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
            Some(parser.parse_type_field())
        });
        self.expect(TokenKind::RightBrace, vec![TokenKind::Identifier]);

        TypeDeclarationNode {
            location: self.get_location(start),
            name,
            bases,
            fields,
        }
    }

    #[inline]
    fn parse_parameter(&mut self) -> ParameterNode {
        let start = self.current_source_position();
        let name = self.parse_identifier_from_parameter(vec![
            TokenKind::Colon,
            TokenKind::Identifier,
            TokenKind::Comma,
            TokenKind::RightParenthesis,
            TokenKind::LeftBrace,
            TokenKind::RightBrace,
        ]);

        let optional = match self.expect_optional(
            TokenKind::Question,
            vec![
                TokenKind::Colon,
                TokenKind::Identifier,
                TokenKind::Comma,
                TokenKind::RightParenthesis,
                TokenKind::LeftBrace,
                TokenKind::RightBrace,
            ],
        ) {
            Some(_) => true,
            _ => false,
        };

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

        ParameterNode {
            location: self.get_location(start),
            optional,
            name,
            type_name,
        }
    }

    #[inline]
    fn consume_int_literal(&mut self) -> IntLiteralNode {
        let token = self.current().unwrap();
        debug_assert_eq!(token.kind, TokenKind::Int);
        self.advance(1);
        let index = token.position.offset;
        IntLiteralNode {
            location: token.position,
            neg: self.data[index] == 45,
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
    fn consume_null_literal(&mut self) -> NullLiteralNode {
        let token = self.current().unwrap();
        debug_assert_eq!(token.kind, TokenKind::Null);
        self.advance(1);
        NullLiteralNode {
            location: token.position,
        }
    }

    #[inline]
    fn consume_string_literal(&mut self) -> StringLiteralNode {
        let token = self.current().unwrap();
        debug_assert_eq!(token.kind, TokenKind::String);
        self.advance(1);
        StringLiteralNode {
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
                TokenKind::Null,
                TokenKind::String,
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
                    TokenKind::RightBrace,
                    TokenKind::Parameter,
                    TokenKind::InternalVariable,
                    TokenKind::Boolean,
                    TokenKind::Null,
                    TokenKind::String,
                    TokenKind::Int,
                    TokenKind::Float,
                ],
                |parser| {
                    parser.parse_identifier(vec![
                        TokenKind::Dot,
                        TokenKind::Comma,
                        TokenKind::RightParenthesis,
                        TokenKind::RightBrace,
                        TokenKind::Parameter,
                        TokenKind::InternalVariable,
                        TokenKind::Boolean,
                        TokenKind::Null,
                        TokenKind::String,
                        TokenKind::Int,
                        TokenKind::Float,
                    ])
                },
                TokenKind::Dot,
                false,
            );
        }

        AccessNode {
            location: self.get_location(start),
            base,
            parts,
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
                ValueNode::Call(self.parse_call())
            }
            None => {
                self.current_token_index = current_index;
                ValueNode::Type(self.consume_type_reference())
            }
        }
    }

    #[inline(always)]
    fn parse_value_primary(&mut self) -> Option<ValueNode> {
        match self.find_first_of(
            &vec![
                TokenKind::Dot,
                TokenKind::Identifier,
                TokenKind::LeftParenthesis,
                TokenKind::LeftBrace,
                TokenKind::Parameter,
                TokenKind::InternalVariable,
                TokenKind::Boolean,
                TokenKind::Null,
                TokenKind::String,
                TokenKind::Int,
                TokenKind::Float,
                TokenKind::CreateKeyword,
            ],
            vec![
                TokenKind::Comma,
                TokenKind::RightBrace,
                TokenKind::RightParenthesis,
            ],
        ) {
            Some(TokenKind::LeftBrace) => Some(ValueNode::Query(self.parse_query())),
            Some(TokenKind::Int) => Some(ValueNode::Int(self.consume_int_literal())),
            Some(TokenKind::Float) => Some(ValueNode::Float(self.consume_float_literal())),
            Some(TokenKind::Boolean) => Some(ValueNode::Boolean(self.consume_boolean_literal())),
            Some(TokenKind::Null) => Some(ValueNode::Null(self.consume_null_literal())),
            Some(TokenKind::String) => Some(ValueNode::String(self.consume_string_literal())),
            Some(TokenKind::Dot)
            | Some(TokenKind::Parameter)
            | Some(TokenKind::InternalVariable) => Some(ValueNode::Access(self.consume_access())),
            Some(TokenKind::LeftParenthesis) => Some(ValueNode::Call(self.parse_call())),
            Some(TokenKind::Identifier) => Some(self.consume_type_reference_or_call()),
            Some(TokenKind::CreateKeyword) => {
                Some(ValueNode::Create(self.parse_create_statement()))
            }
            _ => None,
        }
    }

    #[inline(always)]
    fn parse_value_0(&mut self, lhs_: Option<ValueNode>, min_precedence: i8) -> Option<ValueNode> {
        let mut lookahead = self.current();
        let mut lhs = lhs_;
        loop {
            if let Some(token) = lookahead {
                let precedence = get_precedence(token.kind);
                if precedence < min_precedence {
                    break;
                }

                let op = token;
                self.advance(1);
                let mut rhs = self.parse_value_primary();

                lookahead = self.current();
                while lookahead.is_some() && get_precedence(lookahead.unwrap().kind) > precedence {
                    rhs = self.parse_value_0(rhs, precedence);
                    lookahead = self.current();
                }

                let mut start = op.position.offset;
                let mut arguments = Vec::with_capacity(2);
                if let Some(arg) = lhs {
                    start = arg.get_location().offset;
                    arguments.push(arg);
                }

                if let Some(arg) = rhs {
                    arguments.push(arg);
                }

                lhs = Some(ValueNode::Call(CallNode {
                    location: self.get_location(start),
                    callee_name: Some(IdentifierNode {
                        location: op.position,
                        value: String::from(match op.kind {
                            TokenKind::Add => "add",
                            TokenKind::Sub => "sub",
                            TokenKind::Mul => "mul",
                            TokenKind::Div => "div",
                            _ => unimplemented!(),
                        }),
                    }),
                    arguments,
                }))
            } else {
                break;
            }
        }
        lhs
    }

    #[inline]
    fn parse_value(&mut self) -> Option<ValueNode> {
        let lhs = self.parse_value_primary();
        self.parse_value_0(lhs, 0)
    }

    #[inline(always)]
    fn parse_call(&mut self) -> CallNode {
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
            //
            TokenKind::Semicolon,
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
            vec![TokenKind::RightBrace, TokenKind::RightParenthesis],
            |parser| parser.parse_value(),
            false,
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

        CallNode {
            location: self.get_location(start),
            callee_name: name,
            arguments,
        }
    }

    #[inline]
    fn parse_query(&mut self) -> QueryNode {
        let start = self.current_source_position();
        let mut pipelines: Vec<CallNode> = vec![];

        self.expect(
            TokenKind::LeftBrace,
            vec![TokenKind::Identifier, TokenKind::LeftParenthesis],
        );

        self.collect_comma_separated(
            &mut pipelines,
            vec![
                TokenKind::RightBrace,
                TokenKind::TypeKeyword,
                TokenKind::ActionKeyword,
                TokenKind::PermissionKeyword,
                TokenKind::QueryKeyword,
            ],
            |parser| Some(parser.parse_call()),
            true,
        );

        self.expect(
            TokenKind::RightBrace,
            vec![
                TokenKind::TypeKeyword,
                TokenKind::ActionKeyword,
                TokenKind::PermissionKeyword,
                TokenKind::QueryKeyword,
                TokenKind::Identifier,
            ],
        );

        QueryNode {
            location: self.get_location(start),
            pipelines,
        }
    }

    #[inline]
    fn parse_with_parameter_header(&mut self) -> (Option<IdentifierNode>, Vec<ParameterNode>) {
        let name = self.parse_identifier(vec![
            TokenKind::LeftParenthesis,
            TokenKind::LeftBrace,
            TokenKind::Parameter,
            TokenKind::Question,
            TokenKind::Colon,
            TokenKind::AllowKeyword,
        ]);
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
                TokenKind::AllowKeyword,
            ],
        );

        self.collect_comma_separated(
            &mut parameters,
            vec![
                TokenKind::LeftBrace,
                TokenKind::RightParenthesis,
                TokenKind::AllowKeyword,
            ],
            |parser| Some(parser.parse_parameter()),
            true,
        );

        self.expect(
            TokenKind::RightParenthesis,
            vec![
                TokenKind::LeftBrace,
                TokenKind::RightBrace,
                TokenKind::Identifier,
                TokenKind::LeftParenthesis,
                TokenKind::AllowKeyword,
            ],
        );

        (name, parameters)
    }

    /// Parse a query declaration assuming that the `query` token is already
    /// seen but not consumed.
    #[inline]
    fn parse_query_declaration(&mut self) -> QueryDeclarationNode {
        debug_assert!(self.current().unwrap().kind == TokenKind::QueryKeyword);
        let start = self.current_source_position();
        self.advance(1);

        let (name, parameters) = self.parse_with_parameter_header();
        let mut guards: Vec<GuardNode> = Vec::new();
        self.collect(
            &mut guards,
            vec![
                TokenKind::LeftBrace,
                TokenKind::RightBrace,
                TokenKind::Identifier,
                TokenKind::LeftParenthesis,
            ],
            |parser| parser.parse_guard(),
        );

        let query = self.parse_query();

        QueryDeclarationNode {
            location: self.get_location(start),
            name,
            guards,
            parameters,
            query,
        }
    }

    #[inline]
    fn parse_create_statement(&mut self) -> CreateStatementNode {
        let start = self.current_source_position();
        self.expect(TokenKind::CreateKeyword, vec![TokenKind::Identifier]);

        let base = self.parse_identifier(vec![
            TokenKind::LeftBrace,
            TokenKind::ValidateKeyword,
            TokenKind::CreateKeyword,
            TokenKind::UpdateKeyword,
            TokenKind::DeleteKeyword,
            TokenKind::TypeKeyword,
            TokenKind::ActionKeyword,
            TokenKind::PermissionKeyword,
            TokenKind::QueryKeyword,
            TokenKind::Semicolon,
        ]);
        let binding = self.parse_object_binding();

        CreateStatementNode {
            location: self.get_location(start),
            base,
            binding,
        }
    }

    #[inline]
    fn parse_binding(&mut self) -> FieldBindingNode {
        let start = self.current_source_position();
        let mut uri: Vec<IdentifierNode> = Vec::new();

        self.expect(
            TokenKind::Dot,
            vec![
                TokenKind::Comma,
                TokenKind::Assign,
                TokenKind::Parameter,
                TokenKind::InternalVariable,
                TokenKind::Boolean,
                TokenKind::Null,
                TokenKind::String,
                TokenKind::Int,
                TokenKind::Float,
            ],
        );

        self.collect_separated_by(
            &mut uri,
            vec![
                TokenKind::Assign,
                TokenKind::Comma,
                TokenKind::Semicolon,
                TokenKind::RightBrace,
                TokenKind::Comma,
                TokenKind::LeftParenthesis,
                TokenKind::LeftBrace,
                TokenKind::Parameter,
                TokenKind::InternalVariable,
                TokenKind::Boolean,
                TokenKind::Null,
                TokenKind::String,
                TokenKind::Int,
                TokenKind::Float,
            ],
            |parser| {
                parser.parse_identifier(vec![
                    TokenKind::Dot,
                    TokenKind::Comma,
                    TokenKind::Assign,
                    TokenKind::Parameter,
                    TokenKind::InternalVariable,
                    TokenKind::Boolean,
                    TokenKind::Null,
                    TokenKind::String,
                    TokenKind::Int,
                    TokenKind::Float,
                ])
            },
            TokenKind::Dot,
            false,
        );

        self.expect(
            TokenKind::Assign,
            vec![
                TokenKind::Semicolon,
                TokenKind::Identifier,
                TokenKind::RightBrace,
                TokenKind::Comma,
                TokenKind::Dot,
                TokenKind::LeftParenthesis,
                TokenKind::LeftBrace,
                TokenKind::Parameter,
                TokenKind::InternalVariable,
                TokenKind::Boolean,
                TokenKind::Null,
                TokenKind::String,
                TokenKind::Int,
                TokenKind::Float,
            ],
        );

        let value = self.parse_value();

        FieldBindingNode {
            location: self.get_location(start),
            uri,
            value,
        }
    }

    #[inline]
    fn parse_object_binding(&mut self) -> Option<ObjectBindingNode> {
        let start = self.current_source_position();

        match self.expect(
            TokenKind::LeftBrace,
            vec![
                TokenKind::Identifier,
                TokenKind::LeftParenthesis,
                TokenKind::Semicolon,
            ],
        ) {
            None => {
                return None;
            }
            _ => {}
        };

        let mut bindings: Vec<FieldBindingNode> = vec![];

        self.collect_comma_separated(
            &mut bindings,
            vec![
                TokenKind::RightBrace,
                TokenKind::TypeKeyword,
                TokenKind::ActionKeyword,
                TokenKind::PermissionKeyword,
                TokenKind::QueryKeyword,
                TokenKind::Semicolon,
            ],
            |parser| Some(parser.parse_binding()),
            true,
        );

        self.expect(
            TokenKind::RightBrace,
            vec![
                TokenKind::TypeKeyword,
                TokenKind::ActionKeyword,
                TokenKind::PermissionKeyword,
                TokenKind::QueryKeyword,
                TokenKind::Identifier,
                TokenKind::Semicolon,
            ],
        );

        Some(ObjectBindingNode {
            location: self.get_location(start),
            bindings,
        })
    }

    #[inline]
    fn parse_action_base(&mut self) -> Option<ActionBase> {
        let current = self.current();
        match self.find_first_of(
            &vec![
                TokenKind::LeftBrace,
                TokenKind::Parameter,
                TokenKind::InternalVariable,
            ],
            vec![
                TokenKind::Semicolon,
                TokenKind::RightBrace,
                TokenKind::ValidateKeyword,
                TokenKind::CreateKeyword,
                TokenKind::UpdateKeyword,
                TokenKind::DeleteKeyword,
            ],
        ) {
            // It might possibly be an `Object Binding` so we use up to 2 lookahead tokens
            // to make sure that this is actually a `Query`.
            Some(TokenKind::LeftBrace) => match self.lookahead(1) {
                Some(token) => match token.kind {
                    TokenKind::Identifier => match self.lookahead(2) {
                        Some(l2) => match l2.kind {
                            TokenKind::Dot | TokenKind::Colon => {
                                self.report(Diagnostic::expected_action_base(current.unwrap()));
                                None
                            }
                            _ => Some(ActionBase::Query(self.parse_query())),
                        },
                        None => Some(ActionBase::Query(self.parse_query())),
                    },
                    TokenKind::RightBrace | TokenKind::LeftParenthesis => {
                        Some(ActionBase::Query(self.parse_query()))
                    }
                    _ => {
                        self.report(Diagnostic::expected_action_base(current.unwrap()));
                        None
                    }
                },
                None => {
                    self.report(Diagnostic::expected_action_base(current.unwrap()));
                    None
                }
            },
            Some(_) => Some(ActionBase::Access(self.consume_access())),
            _ => None,
        }
    }

    #[inline]
    fn parse_action_statement(&mut self) -> Option<ActionStatement> {
        let semicolon_breaks = vec![
            TokenKind::RightBrace,
            TokenKind::ValidateKeyword,
            TokenKind::CreateKeyword,
            TokenKind::UpdateKeyword,
            TokenKind::DeleteKeyword,
            TokenKind::TypeKeyword,
            TokenKind::ActionKeyword,
            TokenKind::PermissionKeyword,
            TokenKind::QueryKeyword,
        ];

        match self.find_first_of(
            &vec![
                TokenKind::ValidateKeyword,
                TokenKind::CreateKeyword,
                TokenKind::UpdateKeyword,
                TokenKind::DeleteKeyword,
            ],
            vec![
                TokenKind::RightBrace,
                TokenKind::TypeKeyword,
                TokenKind::ActionKeyword,
                TokenKind::PermissionKeyword,
                TokenKind::QueryKeyword,
            ],
        ) {
            Some(TokenKind::ValidateKeyword) => {
                let start = self.current_source_position();
                self.advance(1);
                let value = match self.find_first_of(
                    &vec![TokenKind::Identifier, TokenKind::LeftParenthesis],
                    vec![
                        TokenKind::Semicolon,
                        TokenKind::RightBrace,
                        TokenKind::ValidateKeyword,
                        TokenKind::CreateKeyword,
                        TokenKind::UpdateKeyword,
                        TokenKind::DeleteKeyword,
                        TokenKind::TypeKeyword,
                        TokenKind::ActionKeyword,
                        TokenKind::PermissionKeyword,
                        TokenKind::QueryKeyword,
                    ],
                ) {
                    Some(_) => Some(self.parse_call()),
                    _ => None,
                };
                let location = self.get_location(start);
                self.expect(TokenKind::Semicolon, semicolon_breaks);
                Some(ActionStatement::Validate(ValidateStatementNode {
                    location,
                    value,
                }))
            }
            Some(TokenKind::CreateKeyword) => {
                let stmt = self.parse_create_statement();
                self.expect(TokenKind::Semicolon, semicolon_breaks);
                Some(ActionStatement::Create(stmt))
            }
            Some(TokenKind::UpdateKeyword) => {
                let start = self.current_source_position();
                self.advance(1);
                let base = self.parse_action_base();
                let updates = self.parse_object_binding();
                let location = self.get_location(start);
                self.expect(TokenKind::Semicolon, semicolon_breaks);
                Some(ActionStatement::Update(UpdateStatementNode {
                    location,
                    base,
                    updates,
                }))
            }
            Some(TokenKind::DeleteKeyword) => {
                let start = self.current_source_position();
                self.advance(1);
                let base = self.parse_action_base();
                let location = self.get_location(start);
                self.expect(TokenKind::Semicolon, semicolon_breaks);
                Some(ActionStatement::Delete(DeleteStatementNode {
                    location,
                    base,
                }))
            }
            _ => None,
        }
    }

    #[inline]
    fn parse_permission_declaration(&mut self) -> PermissionDeclarationNode {
        debug_assert!(self.current().unwrap().kind == TokenKind::PermissionKeyword);
        let start = self.current_source_position();
        self.advance(1);

        let (name, parameters) = self.parse_with_parameter_header();
        let query = self.parse_query();

        PermissionDeclarationNode {
            location: self.get_location(start),
            name,
            parameters,
            query,
        }
    }

    #[inline]
    fn parse_action_declaration(&mut self) -> ActionDeclarationNode {
        debug_assert!(self.current().unwrap().kind == TokenKind::ActionKeyword);
        let start = self.current_source_position();
        self.advance(1);

        let (name, parameters) = self.parse_with_parameter_header();
        let mut guards: Vec<GuardNode> = Vec::new();
        let mut statements: Vec<ActionStatement> = Vec::new();

        self.collect(
            &mut guards,
            vec![
                TokenKind::LeftBrace,
                TokenKind::RightBrace,
                TokenKind::Identifier,
                TokenKind::LeftParenthesis,
            ],
            |parser| parser.parse_guard(),
        );

        self.expect(
            TokenKind::LeftBrace,
            vec![TokenKind::Identifier, TokenKind::LeftParenthesis],
        );

        self.collect(
            &mut statements,
            vec![
                TokenKind::RightBrace,
                TokenKind::TypeKeyword,
                TokenKind::ActionKeyword,
                TokenKind::PermissionKeyword,
                TokenKind::QueryKeyword,
            ],
            |parser| parser.parse_action_statement(),
        );

        self.expect(
            TokenKind::RightBrace,
            vec![
                TokenKind::TypeKeyword,
                TokenKind::ActionKeyword,
                TokenKind::PermissionKeyword,
                TokenKind::QueryKeyword,
                TokenKind::Identifier,
            ],
        );

        ActionDeclarationNode {
            location: self.get_location(start),
            name,
            guards,
            parameters,
            statements,
        }
    }

    fn parse_guard(&mut self) -> Option<GuardNode> {
        let start = self.current_source_position();

        match self.expect_optional(
            TokenKind::AllowKeyword,
            vec![
                TokenKind::LeftBrace,
                TokenKind::RightBrace,
                TokenKind::TypeKeyword,
                TokenKind::PermissionKeyword,
                TokenKind::ActionKeyword,
                TokenKind::QueryKeyword,
            ],
        ) {
            Some(_) => {}
            None => return None,
        }

        let call = match self.find_first_of(
            &vec![TokenKind::Identifier, TokenKind::LeftParenthesis],
            vec![
                TokenKind::LeftBrace,
                TokenKind::RightBrace,
                TokenKind::TypeKeyword,
                TokenKind::PermissionKeyword,
                TokenKind::ActionKeyword,
                TokenKind::QueryKeyword,
            ],
        ) {
            Some(_) => Some(self.parse_call()),
            _ => None,
        };

        Some(GuardNode {
            location: self.get_location(start),
            call,
        })
    }

    pub fn parse_declaration(&mut self) -> Option<Declaration> {
        if self.tokenizer.is_eof() {
            return None;
        }

        match self.current() {
            None => return None,
            _ => {}
        }

        match self.find_first_of(
            &vec![
                TokenKind::QueryKeyword,
                TokenKind::TypeKeyword,
                TokenKind::ActionKeyword,
                TokenKind::PermissionKeyword,
            ],
            vec![],
        ) {
            Some(TokenKind::TypeKeyword) => {
                Some(Declaration::Type(Rc::new(self.parse_type_declaration())))
            }
            Some(TokenKind::QueryKeyword) => {
                Some(Declaration::Query(Rc::new(self.parse_query_declaration())))
            }
            Some(TokenKind::ActionKeyword) => Some(Declaration::Action(Rc::new(
                self.parse_action_declaration(),
            ))),
            Some(TokenKind::PermissionKeyword) => Some(Declaration::Permission(Rc::new(
                self.parse_permission_declaration(),
            ))),
            _ => None,
        }
    }
}

#[inline(always)]
fn get_precedence(kind: TokenKind) -> i8 {
    match kind {
        TokenKind::Add => 1,
        TokenKind::Sub => 1,
        TokenKind::Mul => 2,
        TokenKind::Div => 2,
        _ => -1,
    }
}
