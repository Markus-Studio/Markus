#![allow(dead_code)]
use crate::parser::tokenizer::{Span, Token, TokenKind};

#[derive(Copy, Clone, PartialEq, Debug)]
pub enum DiagnosticKind {
    EarlyEndOfFile,
    UnexpectedToken(Option<TokenKind>),
}

/// A diagnostic is an error happing in any phase from parsing to
/// type validation and so on.
#[derive(Copy, Clone, PartialEq, Debug)]
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
}
