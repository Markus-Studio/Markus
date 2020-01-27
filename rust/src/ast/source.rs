use crate::ast::diagnostics;

/// The Source is used to store each source file and all of the diagnostics
/// related to them.
pub struct Source<'a> {
    /// The file name which this source is derived from.
    filename: String,
    /// The data in the file.
    data: &'a str,
    /// All of the errors we encountered on this source file.
    diagnostics: Vec<diagnostics::Diagnostic>,
}

impl<'a> Source<'a> {
    /// Constructs a new Source struct with the given filename and data.
    pub fn new(filename: String, data: &'a str) -> Source<'a> {
        Source {
            filename: filename,
            data: data,
            diagnostics: vec![],
        }
    }

    /// Returns true if there is no error attached to this source file.
    #[inline]
    pub fn is_good(&self) -> bool {
        self.diagnostics.is_empty()
    }

    #[inline]
    pub fn get_filename(&self) -> String {
        String::from(&self.filename)
    }

    /// Use this function to report an error on the source file.
    pub fn report(&mut self, diagnostic: diagnostics::Diagnostic) {
        self.diagnostics.push(diagnostic);
    }

    #[inline]
    pub fn get_data(&self) -> &'a str {
        &self.data
    }
}
