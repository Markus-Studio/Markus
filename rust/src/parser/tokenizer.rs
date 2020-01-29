#![allow(dead_code)]
use crate::parser::diagnostics::Diagnostic;

#[derive(Copy, Clone)]
pub enum Token {
    LeftParenthesis,
    RightParenthesis,
    LeftBrace,
    RightBrace,
    Dot,
    Comma,
    Semicolon,
    Colon,
    At,
    Identifier { start: usize, size: usize },
    Parameter { start: usize, size: usize },
    InternalVariable { start: usize, size: usize },
    Int { start: usize, size: usize },
    Float { start: usize, size: usize },
}

pub struct Tokenizer<'a> {
    data: &'a Vec<u16>,
    pub position: usize,
    occurred_error: bool,
    diagnostic: Diagnostic,
}

impl<'a> Tokenizer<'a> {
    pub fn new(data: &'a Vec<u16>, position: usize) -> Tokenizer<'a> {
        Tokenizer {
            data: data,
            position: position,
            occurred_error: false,
            diagnostic: Diagnostic::NoDiagnostic,
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
            String::from_utf16(&[self.data[self.position]])
                .unwrap()
                .chars()
                .next()
        }
    }

    #[inline]
    fn char_unchecked(&self) -> char {
        String::from_utf16(&[self.data[self.position]])
            .unwrap()
            .chars()
            .next()
            .unwrap()
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
    fn report(&mut self, diagnostic: Diagnostic) {
        self.occurred_error = true;
        self.diagnostic = diagnostic;
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
                self.report(Diagnostic::UnexpectedCharacter {
                    position: self.position,
                });
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
                            self.report(Diagnostic::UnexpectedCharacter {
                                position: self.position,
                            });
                            return None;
                        }
                    }
                }
                _ => break,
            }
        }

        if seen_float_point {
            Some(Token::Float {
                start: start,
                size: self.position - start,
            })
        } else {
            Some(Token::Int {
                start: start,
                size: self.position - start,
            })
        }
    }

    #[inline]
    fn read_next_token(&mut self) -> Option<Token> {
        if self.occurred_error {
            return None;
        }

        self.consume_blank();

        if self.is_eof() {
            return None;
        }

        match self.char_unchecked() {
            '(' => {
                self.advance(1);
                Some(Token::LeftParenthesis)
            }
            ')' => {
                self.advance(1);
                Some(Token::RightParenthesis)
            }
            '{' => {
                self.advance(1);
                Some(Token::LeftBrace)
            }
            '}' => {
                self.advance(1);
                Some(Token::RightBrace)
            }
            ',' => {
                self.advance(1);
                Some(Token::Comma)
            }
            ';' => {
                self.advance(1);
                Some(Token::Semicolon)
            }
            ':' => {
                self.advance(1);
                Some(Token::Colon)
            }
            '@' => {
                self.advance(1);
                Some(Token::At)
            }
            '.' => {
                self.advance(1);
                Some(Token::Dot)
            }
            '$' => {
                self.advance(1);
                let start = self.position;
                match self.eat_identifier() {
                    Some(size) => Some(Token::Parameter {
                        start: start,
                        size: size,
                    }),
                    None => None,
                }
            }
            '%' => {
                self.advance(1);
                let start = self.position;
                match self.eat_identifier() {
                    Some(size) => Some(Token::InternalVariable {
                        start: start,
                        size: size,
                    }),
                    None => None,
                }
            }
            '0'..='9' => self.eat_numeric_token(),
            c if is_identifier_start(c) => {
                let start = self.position;
                match self.eat_identifier() {
                    Some(size) => Some(Token::Identifier {
                        start: start,
                        size: size,
                    }),
                    None => None,
                }
            }
            _ => {
                self.report(Diagnostic::UnexpectedCharacter {
                    position: self.position,
                });
                None
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

impl Token {
    pub fn is_identifer(&self) -> bool {
        match self {
            Token::Identifier { start: _, size: _ } => true,
            _ => false,
        }
    }

    pub fn compare_identifier(&self, data: &Vec<u16>, word: &str) -> bool {
        match self {
            Token::Identifier { start, size } => {
                let w16: Vec<u16> = word.encode_utf16().collect();
                if w16.len() != *size {
                    false
                } else {
                    data[*start..*start + *size] == w16[0..*size]
                }
            }
            _ => false,
        }
    }
}
