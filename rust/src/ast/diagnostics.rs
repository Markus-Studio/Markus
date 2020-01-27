/// A diagnostic is an error happing in any phase from parsing to
/// type validation and so on.
pub enum Diagnostic {
    UnexpectedCharacter { position: usize },
    EarlyEndOfFile,
}
