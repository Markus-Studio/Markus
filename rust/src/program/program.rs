#![allow(dead_code)]
use crate::parser::ast::Declaration;
use crate::parser::Parser;
use crate::parser::Source;
use crate::program::diagnostics;

pub struct Program {
    pub source: Source,
    pub declarations: Vec<Declaration>,
    /// All of the errors we encountered on this source file.
    pub diagnostics: Vec<diagnostics::Diagnostic>,
}

impl Program {
    /// Constructs a new program from the given source file, but it does not
    /// parse the data, you should call .parse() after the construction.
    pub fn new(source: Source) -> Program {
        Program {
            source: source,
            declarations: vec![],
            diagnostics: vec![],
        }
    }

    /// Returns true if there is no error attached to this source file.
    pub fn is_good(&self) -> bool {
        self.diagnostics.is_empty()
    }

    /// Use this function to report an error on this source file.
    #[inline]
    pub fn report(&mut self, diagnostic: diagnostics::Diagnostic) {
        self.diagnostics.push(diagnostic);
    }

    /// Hard parse the source code.
    pub fn parse(&mut self) {
        self.declarations.clear();
        self.diagnostics.clear();

        let mut parser = Parser::new(&self.source.content, 0);
        loop {
            match parser.parse_declaration() {
                Some(declaration) => {
                    self.declarations.push(declaration);
                }
                None => break,
            }
        }

        for diagnostic in parser.diagnostics {
            self.report(diagnostic);
        }
    }

    pub fn verify(&mut self) {

    }
}
