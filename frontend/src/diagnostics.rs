use super::shared::Range;
use strum::EnumMessage;

#[derive(Copy, Clone, PartialEq, Debug, Hash)]
pub struct Diagnostic {
    pub location: Option<Range>,
    pub kind: DiagnosticKind,
}

#[derive(EnumMessage, Copy, Clone, PartialEq, Debug, Hash)]
pub enum DiagnosticKind {
    #[strum(message = "Name already in use.")]
    NameAlreadyInUse,
    // Errors related to a single type declaration
    #[strum(message = "Base create circular dependency.")]
    CircularBaseGraph,
    #[strum(message = "A base must be an object-type.")]
    AtomicTypeUsedAsBase,
    #[strum(message = "The following field name is already in use.")]
    FieldNameAlreadyInUse,
    #[strum(message = "The following field name is present somewhere at the base graph.")]
    FieldNameAppearsInParent,
    #[strum(message = "Recursive (circular) field must be nullable.")]
    RequiredCircularField,
    // permission declaration errors:
    #[strum(message = "Permission reaches NEVER.")]
    EmptyPermissionSelector,
    // general query errors:
    #[strum(message = "Selector reaches NEVER.")]
    SelectorReachesNull,
    #[strum(message = "Pipeline not found.")]
    PipelineNotFound,
    #[strum(message = "Wrong number of arguments in the call.")]
    MismatchingArgument,
    #[strum(message = "Field not found on the type.")]
    FieldNotFound,
    #[strum(message = "Cannot resolve name.")]
    CannotResolveName,
    // type errors:
    #[strum(message = "Cannot mix types with different ranks.")]
    TypeMixedRank,
    // parser errors:
    #[strum(message = "Expected identifier token.")]
    MissingIdentifier,
    #[strum(message = "Expected field type.")]
    MissingFieldType,
}

impl Diagnostic {
    pub fn new(kind: DiagnosticKind, location: Option<Range>) -> Diagnostic {
        Diagnostic { location, kind }
    }

    pub fn attach_location(&mut self, range: Range) {
        self.location = Some(range);
    }
}

impl std::fmt::Display for Diagnostic {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.kind.get_message().unwrap())
    }
}
