#[derive(Copy, Clone, Debug, PartialEq)]
pub enum TokenKind {
    /// An unknown character.
    Unknown,
    /// `(` Token.
    LeftParenthesis,
    /// `)` Token.
    RightParenthesis,
    /// `{` Token.
    LeftBrace,
    /// `}` Token.
    RightBrace,
    /// `.` Token.
    Dot,
    /// `,` Token.
    Comma,
    /// ';' Token.
    Semicolon,
    /// `:` Token.
    Colon,
    /// `?` Token.
    Question,
    /// `+` Token.
    Add,
    /// `-` Token.
    Sub,
    /// `\` Token.
    Div,
    /// `*` Token.
    Mul,
    /// An identifier token.
    Identifier,
    /// $[identifier] Token.
    Parameter,
    /// %[identifier] Token.
    InternalVariable,
    /// true | false
    Boolean,
    /// An integer literal token.
    Int,
    /// A float literal token.
    Float,
    // An string literal token.
    String,
    // `null` literal, it can't be referenced as a type.
    Null,
    /// `query` keyword.
    QueryKeyword,
    /// `type` keyword.
    TypeKeyword,
    /// `action` keyword.
    ActionKeyword,
    /// `permission` keyword.
    PermissionKeyword,
    /// `validate` keyword.
    ValidateKeyword,
    /// `create` keyword.
    CreateKeyword,
    /// `update` keyword.
    UpdateKeyword,
    /// `delete` keyword.
    DeleteKeyword,
    /// `for` keyword.
    ForKeyword,
    /// `in` keyword.
    InKeyword,
    /// `allow` keyword.
    AllowKeyword,
}

#[derive(PartialEq, Copy, Clone, Debug)]
pub struct Span {
    pub offset: usize,
    pub size: usize,
}

#[derive(Copy, Clone, Debug)]
pub struct Token {
    pub position: Span,
    pub kind: TokenKind,
}

pub struct Tokenizer<'a> {
    data: &'a Vec<u16>,
    pub position: usize,
}

impl<'a> Tokenizer<'a> {
    pub fn new(data: &'a Vec<u16>, position: usize) -> Tokenizer<'a> {
        Tokenizer { data, position }
    }

    #[inline]
    fn char(&self) -> Option<char> {
        if self.is_eof() {
            None
        } else {
            std::char::from_u32(self.data[self.position] as u32)
        }
    }

    #[inline]
    fn char_unchecked(&self) -> char {
        std::char::from_u32(self.data[self.position] as u32).unwrap()
    }

    #[inline]
    fn has_at_least(&self, n: usize) -> bool {
        self.position + n < self.data.len()
    }

    #[inline]
    pub fn is_eof(&self) -> bool {
        !self.has_at_least(0)
    }

    #[inline]
    fn advance(&mut self, n: usize) {
        self.position += n;
    }

    #[inline]
    fn consume_blank(&mut self) {
        loop {
            match self.char() {
                // Usual ASCII suspects
                | Some('\u{0009}') // \t
                | Some('\u{000A}') // \n
                | Some('\u{000B}') // vertical tab
                | Some('\u{000C}') // form feed
                | Some('\u{000D}') // \r
                | Some('\u{0020}') // space
                // NEXT LINE from latin1
                | Some('\u{0085}')
                // Bidi markers
                | Some('\u{200E}') // LEFT-TO-RIGHT MARK
                | Some('\u{200F}') // RIGHT-TO-LEFT MARK
                // Dedicated whitespace characters from Unicode
                | Some('\u{2028}') // LINE SEPARATOR
                | Some('\u{2029}') // PARAGRAPH SEPARATOR
                => {
                    self.advance(1);
                }
                _ => break,
            }
        }
    }

    #[inline]
    fn eat_identifier(&mut self) -> Option<usize> {
        let mut size = 0;

        match self.char() {
            Some(c) if is_identifier_start(c) => {
                size += 1;
                self.advance(1);
            }
            _ => {
                return None;
            }
        }

        loop {
            match self.char() {
                Some(c) if is_identifier_part(c) => {
                    self.advance(1);
                    size += 1;
                }
                _ => break,
            }
        }

        Some(size)
    }

    #[inline]
    fn eat_numeric_token(&mut self) -> Option<Token> {
        let start = self.position;
        self.advance(1);
        let mut seen_float_point = false;

        loop {
            match self.char() {
                Some(c) if is_digit(c) => {
                    self.advance(1);
                }
                Some('.') if !seen_float_point => {
                    self.advance(1);
                    seen_float_point = true;

                    match self.char() {
                        Some(c) if is_digit(c) => {
                            self.advance(1);
                        }
                        _ => {
                            self.position -= 1; // release the consumed `.`.
                            seen_float_point = false;
                            break;
                        }
                    }
                }
                _ => break,
            }
        }

        Some(Token::new(
            match seen_float_point {
                true => TokenKind::Float,
                false => TokenKind::Int,
            },
            start,
            self.position - start,
        ))
    }

    #[inline]
    fn read_next_token(&mut self) -> Option<Token> {
        self.consume_blank();

        if self.is_eof() {
            return None;
        }

        let start = self.position;

        match self.char_unchecked() {
            '#' => {
                // Comment.
                loop {
                    match self.char() {
                        Some(c) if c != '\n' => {
                            self.advance(1);
                        }
                        _ => {
                            break;
                        }
                    }
                }
                self.read_next_token()
            }
            '"' => {
                // String literal.
                self.advance(1);
                let mut escaped = false;
                loop {
                    match self.char() {
                        Some('\\') => {
                            escaped = !escaped;
                            self.advance(1);
                        }
                        Some('"') if !escaped => {
                            self.advance(1);
                            break;
                        }
                        Some('\n') | None => {
                            self.position = start;
                            self.advance(1);
                            return Some(Token::new(TokenKind::Unknown, start, 1));
                        }
                        Some(_) => {
                            escaped = false;
                            self.advance(1);
                        }
                    }
                }

                Some(Token::new(TokenKind::String, start, self.position - start))
            }
            '(' => {
                self.advance(1);
                Some(Token::new(TokenKind::LeftParenthesis, start, 1))
            }
            ')' => {
                self.advance(1);
                Some(Token::new(TokenKind::RightParenthesis, start, 1))
            }
            '{' => {
                self.advance(1);
                Some(Token::new(TokenKind::LeftBrace, start, 1))
            }
            '}' => {
                self.advance(1);
                Some(Token::new(TokenKind::RightBrace, start, 1))
            }
            ',' => {
                self.advance(1);
                Some(Token::new(TokenKind::Comma, start, 1))
            }
            ';' => {
                self.advance(1);
                Some(Token::new(TokenKind::Semicolon, start, 1))
            }
            ':' => {
                self.advance(1);
                Some(Token::new(TokenKind::Colon, start, 1))
            }
            '?' => {
                self.advance(1);
                Some(Token::new(TokenKind::Question, start, 1))
            }
            '+' => {
                self.advance(1);
                Some(Token::new(TokenKind::Add, start, 1))
            }
            '-' => {
                self.advance(1);
                Some(Token::new(TokenKind::Sub, start, 1))
            }
            '\\' => {
                self.advance(1);
                Some(Token::new(TokenKind::Div, start, 1))
            }
            '*' => {
                self.advance(1);
                Some(Token::new(TokenKind::Mul, start, 1))
            }
            '.' => {
                self.advance(1);
                Some(Token::new(TokenKind::Dot, start, 1))
            }
            '$' => {
                self.advance(1);
                match self.eat_identifier() {
                    Some(size) => Some(Token::new(TokenKind::Parameter, start, size + 1)),
                    None => Some(Token::new(TokenKind::Unknown, start, 1)),
                }
            }
            '%' => {
                self.advance(1);
                match self.eat_identifier() {
                    Some(size) => Some(Token::new(TokenKind::InternalVariable, start, size + 1)),
                    None => Some(Token::new(TokenKind::Unknown, start, 1)),
                }
            }
            '0'..='9' | '+' | '-' => self.eat_numeric_token(),
            c if is_identifier_start(c) => match self.eat_identifier() {
                Some(size) => {
                    let word = String::from_utf16(&self.data[start..start + size]).unwrap();
                    Some(Token::new(
                        match word.as_str() {
                            "true" | "false" => TokenKind::Boolean,
                            "query" => TokenKind::QueryKeyword,
                            "type" => TokenKind::TypeKeyword,
                            "action" => TokenKind::ActionKeyword,
                            "permission" => TokenKind::PermissionKeyword,
                            "create" => TokenKind::CreateKeyword,
                            "update" => TokenKind::UpdateKeyword,
                            "delete" => TokenKind::DeleteKeyword,
                            "validate" => TokenKind::ValidateKeyword,
                            "for" => TokenKind::ForKeyword,
                            "in" => TokenKind::InKeyword,
                            "allow" => TokenKind::AllowKeyword,
                            "null" => TokenKind::Null,
                            _ => TokenKind::Identifier,
                        },
                        start,
                        size,
                    ))
                }
                None => Some(Token::new(TokenKind::Unknown, start, 1)),
            },
            _ => {
                self.advance(1);
                Some(Token::new(TokenKind::Unknown, start, 1))
            }
        }
    }
}

impl<'a> Iterator for Tokenizer<'a> {
    type Item = Token;

    fn next(&mut self) -> Option<Self::Item> {
        self.read_next_token()
    }
}

#[inline(always)]
fn is_identifier_start(c: char) -> bool {
    match c {
        'a'..='z' | 'A'..='Z' | '_' => true,
        _ => false,
    }
}

#[inline(always)]
fn is_identifier_part(c: char) -> bool {
    match c {
        'a'..='z' | 'A'..='Z' | '0'..='9' | '_' => true,
        _ => false,
    }
}

#[inline(always)]
fn is_digit(c: char) -> bool {
    match c {
        '0'..='9' => true,
        _ => false,
    }
}

impl Token {
    pub fn new(kind: TokenKind, start: usize, size: usize) -> Token {
        Token {
            position: Span::new(start, size),
            kind,
        }
    }
}

impl Span {
    pub fn new(start: usize, size: usize) -> Span {
        Span {
            offset: start,
            size,
        }
    }

    pub fn from_positions(start: usize, end: usize) -> Span {
        Span {
            offset: start,
            size: end - start,
        }
    }
}
