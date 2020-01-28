#![allow(dead_code)]

/// A diagnostic is an error happing in any phase from parsing to
/// type validation and so on.
pub enum Diagnostic {
    NoDiagnostic,
    UnexpectedCharacter { position: usize },
    EarlyEndOfFile,
}
