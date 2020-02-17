use crate::parser::ast::Declaration;
use crate::parser::Parser;
use crate::parser::Source;
use crate::program::{Diagnostic, TypeSpace};

pub struct Program {
    pub source: Source,
    pub declarations: Vec<Declaration>,
    /// All of the errors we encountered on this source file.
    pub diagnostics: Vec<Diagnostic>,
    type_space: TypeSpace,
}

impl Program {
    /// Constructs a new program from the given source file, but it does not
    /// parse the data, you should call .parse() after the construction.
    pub fn new(source: Source) -> Program {
        Program {
            source,
            declarations: vec![],
            diagnostics: vec![],
            type_space: TypeSpace::new_with_builtins(),
        }
    }

    /// Returns true if there is no error attached to this source file.
    pub fn is_good(&self) -> bool {
        self.diagnostics.is_empty()
    }

    /// Use this function to report an error on this source file.
    #[inline]
    pub fn report(&mut self, diagnostic: Diagnostic) {
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
                    match &declaration {
                        Declaration::Type(type_declaration) => {
                            // TODO(qti3e) Handle already in use name, currently panics.
                            self.type_space.add_type(type_declaration.clone());
                        }
                        // TODO(qti3e)
                        _ => {}
                    }
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
        let mut type_errors = self.type_space.verify();
        self.diagnostics.append(&mut type_errors);
        for declaration in &self.declarations {
            match declaration {
                Declaration::Query(query) => {
                    query.verify(&mut self.diagnostics, &self.type_space);
                }
                Declaration::Permission(permission) => {
                    permission.verify(&mut self.diagnostics, &self.type_space);
                }
                _ => {}
            }
        }
    }
}
