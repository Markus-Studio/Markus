use super::shared::Range;

#[derive(Copy, Clone, PartialEq, Debug, Hash)]
pub struct Diagnostic {
    location: Option<Range>,
    kind: DiagnosticKind,
}

#[derive(Copy, Clone, PartialEq, Debug, Hash)]
pub enum DiagnosticKind {
    NameAlreadyInUse,
    // Errors related to a single type declaration
    CircularBaseGraph,
    FieldNameAlreadyInUse,
    FieldNameAppearsInParent,
    RequiredCircularField,
    // permission declaration errors:
    EmptyPermissionSelector,
    // general query errors:
    SelectorReachesNull,
    PipelineNotFound,
    MismatchingArgument,
    FieldNotFound,
    CannotResolveName,
    // type errors:
    TypeMixedRank,
    // parser errors:
    MissingIdentifier,
}

impl Diagnostic {
    pub fn new(kind: DiagnosticKind, location: Option<Range>) -> Diagnostic {
        Diagnostic { location, kind }
    }

    pub fn attach_location(&mut self, range: Range) {
        self.location = Some(range);
    }
}
