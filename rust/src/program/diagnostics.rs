use crate::parser::Source;
use crate::parser::{
    ast::{ActionBase, CallNode, FieldBindingNode, IdentifierNode, ValueNode},
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
    ExpectedActionBase,
    CircularReference,
    ReachedNIL,
    ExpectedArgumentPipeline,
    ExpectedArgumentType,
    ExpectedArgumentField,
    UnexpectedArgument,
    NoMatchingSignature,
    FieldNotFound(String, Vec<String>),
    MismatchedTypes(String, String),
    NilBase,
    BindingTypeError(String, String),
    UpdateAlreadyModifiedField,
    CreateNestedBinding,
    CreateBaseNotObject(String),
    CreateValueNotProvided(String),
}

/// A diagnostic is an error happened in any phase from parsing to
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

    #[inline]
    pub fn expected_action_base(current: Token) -> Diagnostic {
        Diagnostic {
            location: current.position,
            kind: DiagnosticKind::ExpectedActionBase,
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
    pub fn expected_argument_field(node: &ValueNode) -> Diagnostic {
        Diagnostic {
            location: node.get_location(),
            kind: DiagnosticKind::ExpectedArgumentField,
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

    #[inline]
    pub fn field_not_found(type_str: String, uri: Vec<&str>, location: Span) -> Diagnostic {
        let uri_str = uri
            .iter()
            .map(|s| String::from(*s))
            .collect::<Vec<String>>();
        Diagnostic {
            location,
            kind: DiagnosticKind::FieldNotFound(type_str, uri_str),
        }
    }

    #[inline]
    pub fn mismatched_types(type_str1: String, type_str2: String, location: Span) -> Diagnostic {
        Diagnostic {
            location,
            kind: DiagnosticKind::MismatchedTypes(type_str1, type_str2),
        }
    }

    #[inline]
    pub fn nil_base(base: &ActionBase) -> Diagnostic {
        Diagnostic {
            location: base.get_location(),
            kind: DiagnosticKind::NilBase,
        }
    }

    #[inline]
    pub fn binding_type_error(
        field_type: String,
        value_type: String,
        location: Span,
    ) -> Diagnostic {
        Diagnostic {
            location,
            kind: DiagnosticKind::BindingTypeError(field_type, value_type),
        }
    }

    #[inline]
    pub fn update_already_modified_field(location: Span) -> Diagnostic {
        Diagnostic {
            location,
            kind: DiagnosticKind::UpdateAlreadyModifiedField,
        }
    }

    #[inline]
    pub fn create_nested_binding(binding: &FieldBindingNode) -> Diagnostic {
        Diagnostic {
            location: binding.location.to_owned(),
            kind: DiagnosticKind::CreateNestedBinding,
        }
    }

    #[inline]
    pub fn create_base_not_object(identifier: &IdentifierNode) -> Diagnostic {
        let name = identifier.value.to_owned();
        Diagnostic {
            location: identifier.location.to_owned(),
            kind: DiagnosticKind::CreateBaseNotObject(name),
        }
    }

    #[inline]
    pub fn create_value_not_provided(name: String, location: Span) -> Diagnostic {
        Diagnostic {
            location,
            kind: DiagnosticKind::CreateValueNotProvided(name),
        }
    }
}

impl std::string::ToString for Diagnostic {
    fn to_string(&self) -> String {
        match &self.kind {
            DiagnosticKind::EarlyEndOfFile => "Early end of file.".to_string(),
            DiagnosticKind::UnexpectedToken(Some(kind)) => format!("Expected a {} token.", kind),
            DiagnosticKind::UnexpectedToken(None) => "Found unexpected token.".to_string(),
            DiagnosticKind::ExpectedOneOf(tokens) => {
                format!("Expected one of {:?} tokens.", tokens)
            }
            DiagnosticKind::UnresolvedName(name) => format!("Unresolved name `{}`.", name),
            DiagnosticKind::NameAlreadyInUse(name) => format!("Name `{}` is already used.", name),
            DiagnosticKind::BaseNotObject(name) => {
                format!("Can not inherit from non-object type `{}`.", name)
            }
            DiagnosticKind::ExpectedActionBase => "Expected an action-base.".to_string(),
            DiagnosticKind::CircularReference => "Found circular reference.".to_string(),
            DiagnosticKind::ReachedNIL => {
                "The selection reaches an empty-set in the current location.".to_string()
            }
            DiagnosticKind::ExpectedArgumentPipeline => {
                "Function expected a pipeline as the argument.".to_string()
            }
            DiagnosticKind::ExpectedArgumentType => {
                "Function expected a type-reference as the argument.".to_string()
            }
            DiagnosticKind::ExpectedArgumentField => {
                "Function expected a field URI as the argument.".to_string()
            }
            DiagnosticKind::UnexpectedArgument => {
                "Function signature did not expected this argument.".to_string()
            }
            DiagnosticKind::NoMatchingSignature => {
                "No implementation was found matching this call signature.".to_string()
            }
            DiagnosticKind::FieldNotFound(type_name, uri) => {
                let mut uri_str = String::with_capacity(100);
                for part in uri {
                    uri_str.push('.');
                    uri_str.push_str(part);
                }
                format!(
                    "Field `{}` does not exists on type `{}`",
                    uri_str, type_name
                )
            }
            DiagnosticKind::MismatchedTypes(lhs, rhs) => {
                format!("Type `{}` does not match type `{}`", lhs, rhs)
            }
            DiagnosticKind::NilBase => "An action base must not be empty.".to_string(),
            DiagnosticKind::BindingTypeError(field_type, value_type) => format!(
                "Value of type `{}` is not assignable to a field of type `{}`.",
                value_type, field_type
            ),
            DiagnosticKind::UpdateAlreadyModifiedField => {
                "This field is already modified.".to_string()
            }
            DiagnosticKind::CreateNestedBinding => {
                "Nested binding is not allowed in a create statement.".to_string()
            }
            DiagnosticKind::CreateBaseNotObject(name) => {
                format!("Type `{}` is not a user defined object type.", name)
            }
            DiagnosticKind::CreateValueNotProvided(name) => {
                format!("Value of required field `.{}` is not provided.", name)
            }
        }
    }
}

impl Diagnostic {
    pub fn get_uri(&self, source: &Source) -> String {
        let position = source.position_at(self.location.offset);
        format!(
            "{}:{}:{}",
            source.filename,
            position.line + 1,
            position.character + 1
        )
    }
}
