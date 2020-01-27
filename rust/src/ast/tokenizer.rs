use crate::ast::diagnostics::Diagnostic;
use crate::ast::source::Source;

pub enum Token<'a> {
    LeftParenthesis,
    RightParenthesis,
    LeftBrace,
    RightBrace,
    Dot,
    Comma,
    Identifier(&'a str),
    Parameter(&'a str),
    InternalVariable(&'a str),
    Int(i64),
    Float(f64),
}

pub struct Tokenizer<'a> {
    source: &'a mut Source<'a>,
    position: usize,
    current_line_start_position: usize,
    current_line_number: u32,
    occurred_error: bool,
}

impl<'a> Tokenizer<'a> {
    pub fn new(source: &'a mut Source<'a>) -> Tokenizer<'a> {
        Tokenizer {
            source: source,
            position: 0,
            current_line_number: 1,
            current_line_start_position: 0,
            occurred_error: false,
        }
    }

    #[inline]
    fn char(&self) -> Option<char> {
        if self.is_eof() {
            None
        } else {
            Some(
                self.source.get_data()[self.position..]
                    .chars()
                    .next()
                    .unwrap(),
            )
        }
    }

    #[inline]
    fn char_unchecked(&self) -> char {
        self.source.get_data()[self.position..]
            .chars()
            .next()
            .unwrap()
    }

    #[inline]
    fn has_at_least(&self, n: usize) -> bool {
        self.position + n < self.source.get_data().len()
    }

    #[inline]
    fn is_eof(&self) -> bool {
        !self.has_at_least(0)
    }

    #[inline]
    fn advance(&mut self, n: usize) {
        self.position += n;
    }

    #[inline]
    fn report(&mut self, diagnostic: Diagnostic) {
        self.occurred_error = true;
        self.source.report(diagnostic);
    }

    #[inline]
    fn consume_new_line(&mut self) {
        let character = self.char_unchecked();
        self.position += 1;
        if character == '\r' && self.char() == Some('\n') {
            self.position += 1;
        }
        self.current_line_start_position = self.position;
        self.current_line_number += 1;
    }

    #[inline]
    fn consume_blank(&mut self) {
        loop {
            match self.char() {
                Some(' ') | Some('\t') => self.position += 1,
                Some('\r') | Some('\n') => self.consume_new_line(),
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
            None => {
                self.report(Diagnostic::UnexpectedCharacter {
                    position: self.position,
                });
                return None;
            }
            _ => {
                self.report(Diagnostic::EarlyEndOfFile);
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

        Some(&self.source.get_data()[(self.position - size)..self.position])
    }

    #[inline]
    fn eat_numeric_token(&mut self) -> Option<Token<'a>> {
        // TODO(qti3e)
        None
    }

    #[inline]
    fn read_next_token(&mut self) -> Option<Token<'a>> {
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
