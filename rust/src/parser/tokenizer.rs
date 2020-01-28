use crate::parser::diagnostics::Diagnostic;

pub enum Token<'a> {
    LeftParenthesis,
    RightParenthesis,
    LeftBrace,
    RightBrace,
    Dot,
    Comma,
    Semicolon,
    Colon,
    At,
    Identifier(&'a str),
    Parameter(&'a str),
    InternalVariable(&'a str),
    Int(i64),
    Float(f64),
}

pub struct Tokenizer<'a> {
    data: &'a str,
    size: usize,
    position: usize,
    occurred_error: bool,
    diagnostic: Diagnostic,
}

impl<'a> Tokenizer<'a> {
    pub fn new(data: &'a str) -> Tokenizer<'a> {
        Tokenizer {
            data: data,
            size: data.chars().count(),
            position: 0,
            occurred_error: false,
            diagnostic: Diagnostic::NoDiagnostic,
        }
    }

    #[inline]
    fn char(&self) -> Option<char> {
        if self.is_eol() {
            None
        } else {
            Some(self.data[self.position..].chars().next().unwrap())
        }
    }

    #[inline]
    fn char_unchecked(&self) -> char {
        self.data[self.position..].chars().next().unwrap()
    }

    #[inline]
    fn has_at_least(&self, n: usize) -> bool {
        self.position + n < self.size
    }

    #[inline]
    fn is_eol(&self) -> bool {
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
    fn eat_identifier(&mut self) -> Option<&'a str> {
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

        Some(&self.data[(self.position - size)..self.position])
    }

    #[inline]
    fn eat_numeric_token(&mut self) -> Option<Token<'a>> {
        let mut seen_float_point = false;

        let mut integer: i64 = 0;
        let mut floating: f64 = 0.0;
        let mut floating_counter: f64 = 0.1;

        loop {
            match self.char() {
                Some(c) if is_digit(c) => {
                    self.advance(1);

                    if seen_float_point {
                        floating += c.to_digit(10).unwrap() as f64 * floating_counter;
                        floating_counter /= 10.0;
                    } else {
                        integer = integer * 10 + c.to_digit(10).unwrap() as i64;
                    }
                }
                Some('.') if !seen_float_point => {
                    self.advance(1);
                    seen_float_point = true;

                    match self.char() {
                        Some(c) if is_digit(c) => {
                            self.advance(1);
                            floating += c.to_digit(10).unwrap() as f64 * floating_counter;
                            floating_counter /= 10.0;
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
            Some(Token::Float(integer as f64 + floating))
        } else {
            Some(Token::Int(integer))
        }
    }

    #[inline]
    fn read_next_token(&mut self) -> Option<Token<'a>> {
        if self.occurred_error {
            return None;
        }

        self.consume_blank();

        if self.is_eol() {
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
                let tmp = self.eat_identifier();
                match tmp {
                    Some(c) => Some(Token::Parameter(c)),
                    None => None,
                }
            }
            '%' => {
                self.advance(1);
                let tmp = self.eat_identifier();
                match tmp {
                    Some(c) => Some(Token::InternalVariable(c)),
                    None => None,
                }
            }
            '0'..='9' => self.eat_numeric_token(),
            c if is_identifier_start(c) => {
                let tmp = self.eat_identifier();
                match tmp {
                    Some(c) => Some(Token::Identifier(c)),
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
    type Item = Token<'a>;

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
