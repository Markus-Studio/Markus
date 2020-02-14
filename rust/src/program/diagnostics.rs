#![allow(dead_code)]
use crate::parser::{
    ast::{CallNode, IdentifierNode, ValueNode},
    Span, Token, TokenKind,
};

#[derive(PartialEq, Debug)]
pub enum DiagnosticKind {
    EarlyEndOfFile,
    UnexpectedToken(Option<TokenKind>),
    ExpectedOneOf(Vec<TokenKind>),
    UnresolvedName(String),
    NameAlreadyInUse(String),
    BaseNotObject(String),
    CircularReference,
    ReachedNIL,
    ExpectedArgumentPipeline,
    ExpectedArgumentType,
    UnexpectedArgument,
    NoMatchingSignature,
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

    /// Constructs a new unresolved name token at the position of the given token
    /// and with the given name.
    #[inline]
    pub fn unresolved_name(identifier: &IdentifierNode) -> Diagnostic {
        Diagnostic {
            location: identifier.location,
            kind: DiagnosticKind::UnresolvedName(String::from(&identifier.value)),
        }
    }

    #[inline]
    pub fn base_not_object(identifier: &IdentifierNode) -> Diagnostic {
        Diagnostic {
            location: identifier.location,
            kind: DiagnosticKind::BaseNotObject(String::from(&identifier.value)),
        }
    }

    #[inline]
    pub fn name_already_in_use(identifier: &IdentifierNode) -> Diagnostic {
        Diagnostic {
            location: identifier.location,
            kind: DiagnosticKind::NameAlreadyInUse(String::from(&identifier.value)),
        }
    }

    /// Constructs a new circular reference error object.
    #[inline]
    pub fn circular_reference(name_identifier: &IdentifierNode) -> Diagnostic {
        Diagnostic {
            location: name_identifier.location,
            kind: DiagnosticKind::CircularReference,
        }
    }

    #[inline]
    pub fn reached_nil(call: &CallNode) -> Diagnostic {
        Diagnostic {
            location: call.location,
            kind: DiagnosticKind::ReachedNIL,
        }
    }

    #[inline]
    pub fn expected_argument_pipeline(node: &ValueNode) -> Diagnostic {
        Diagnostic {
            location: node.get_location(),
            kind: DiagnosticKind::ExpectedArgumentPipeline,
        }
    }

    #[inline]
    pub fn expected_argument_type(node: &ValueNode) -> Diagnostic {
        Diagnostic {
            location: node.get_location(),
            kind: DiagnosticKind::ExpectedArgumentType,
        }
    }

    #[inline]
    pub fn no_matching_signature(name: &IdentifierNode) -> Diagnostic {
        Diagnostic {
            location: name.location,
            kind: DiagnosticKind::NoMatchingSignature,
        }
    }

    #[inline]
    pub fn unexpected_argument(node: &ValueNode) -> Diagnostic {
        Diagnostic {
            location: node.get_location(),
            kind: DiagnosticKind::UnexpectedArgument,
        }
    }
}
