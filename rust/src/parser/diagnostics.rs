#![allow(dead_code)]
use crate::parser::tokenizer::{Span, Token, TokenKind};

#[derive(PartialEq, Debug)]
pub enum DiagnosticKind {
    EarlyEndOfFile,
    UnexpectedToken(Option<TokenKind>),
    ExpectedOneOf(Vec<TokenKind>),
}

/// A diagnostic is an error happing in any phase from parsing to
/// type validation and so on.
#[derive(PartialEq, Debug)]
pub struct Diagnostic {
    location: Span,
    kind: DiagnosticKind,
}

impl Diagnostic {
    #[inline]
    pub fn expected_token(current: Token, expected: TokenKind) -> Diagnostic {
        Diagnostic {
            location: current.position,
            kind: DiagnosticKind::UnexpectedToken(Some(expected)),
        }
    }

    #[inline]
    pub fn unexpected_token(current: Token) -> Diagnostic {
        Diagnostic {
            location: current.position,
            kind: DiagnosticKind::UnexpectedToken(None),
        }
    }

    #[inline]
    pub fn early_end_of_file(offset: usize) -> Diagnostic {
        Diagnostic {
            location: Span::new(offset, 1),
            kind: DiagnosticKind::EarlyEndOfFile,
        }
    }

    #[inline]
    pub fn expect_one_of(current: Token, expected: &Vec<TokenKind>) -> Diagnostic {
        Diagnostic {
            location: current.position,
            kind: DiagnosticKind::ExpectedOneOf(expected.to_vec()),
        }
    }
}
