#![allow(dead_code)]

#[derive(Copy, Clone, Debug, PartialEq)]
pub enum TokenKind {
    Unknown,
    LeftParenthesis,
    RightParenthesis,
    LeftBrace,
    RightBrace,
    Dot,
    Comma,
    Semicolon,
    Colon,
    At,
    Identifier,
    Parameter,
    InternalVariable,
    Int,
    Float,
}

#[derive(Copy, Clone, Debug)]
pub struct Span {
    pub offset: usize,
    pub size: usize,
}

#[derive(Copy, Clone)]
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
        Tokenizer {
            data: data,
            position: position,
        }
    }

    pub fn set_position(&mut self, position: usize) {
        if position >= self.data.len() {
            panic!("Out of range.");
        }

        self.position = position;
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
            '@' => {
                self.advance(1);
                Some(Token::new(TokenKind::At, start, 1))
            }
            '.' => {
                self.advance(1);
                Some(Token::new(TokenKind::Dot, start, 1))
            }
            '$' => {
                self.advance(1);
                match self.eat_identifier() {
                    Some(size) => Some(Token::new(TokenKind::Parameter, start, size)),
                    None => Some(Token::new(TokenKind::Unknown, start, 1)),
                }
            }
            '%' => {
                self.advance(1);
                match self.eat_identifier() {
                    Some(size) => Some(Token::new(TokenKind::InternalVariable, start, size)),
                    None => Some(Token::new(TokenKind::Unknown, start, 1)),
                }
            }
            '0'..='9' | '+' | '-' => self.eat_numeric_token(),
            c if is_identifier_start(c) => match self.eat_identifier() {
                Some(size) => Some(Token::new(TokenKind::Identifier, start, size)),
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

#[inline]
fn is_identifier_start(c: char) -> bool {
    match c {
        'a'..='z' | 'A'..='Z' | '_' => true,
        _ => false,
    }
}

#[inline]
fn is_identifier_part(c: char) -> bool {
    match c {
        'a'..='z' | 'A'..='Z' | '0'..='9' | '_' => true,
        _ => false,
    }
}

#[inline]
fn is_digit(c: char) -> bool {
    match c {
        '0'..='9' => true,
        _ => false,
    }
}

impl Span {
    pub fn new(start: usize, size: usize) -> Span {
        Span {
            offset: start,
            size: size,
        }
    }
}

impl Token {
    pub fn new(kind: TokenKind, start: usize, size: usize) -> Token {
        Token {
            position: Span::new(start, size),
            kind: kind,
        }
    }

    pub fn is_identifer(&self) -> bool {
        match self.kind {
            TokenKind::Identifier => true,
            _ => false,
        }
    }

    pub fn compare_identifier(&self, data: &Vec<u16>, word: &str) -> bool {
        match self.kind {
            TokenKind::Identifier => {
                let w16: Vec<u16> = word.encode_utf16().collect();
                if w16.len() != self.position.size {
                    false
                } else {
                    data[self.position.offset..self.position.offset + self.position.size]
                        == w16[0..self.position.size]
                }
            }
            _ => false,
        }
    }
}

impl std::fmt::Debug for Token {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "Token(Position({}, {}), {:?})",
            self.position.offset, self.position.size, self.kind
        )
    }
}

impl Span {
    pub fn from_positions(start: usize, end: usize) -> Span {
        Span {
            offset: start,
            size: end - start,
        }
    }
}
