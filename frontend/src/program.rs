use crate::ast::Declaration;
use crate::diagnostics::Diagnostic;
use crate::parser::Parser;
use crate::source::Source;
use crate::types::MarkusType;
use crate::types::TypeSpace;
use common::counter::Counter;
use std::collections::HashMap;
use std::rc::Rc;

pub struct Program {
    pub source: Source,
    /// Every declaration in the same order that has appeared in the source file.
    pub declarations: Vec<Declaration>,
    /// The program's type space that includes every builtin type as well as user
    /// defined types.
    pub type_space: TypeSpace,
    /// Maps a permission name to its (parameter types, return type).
    pub permission_types: HashMap<String, (Vec<Option<MarkusType>>, MarkusType)>,
    /// All of the errors we encountered on this source file.
    pub diagnostics: Vec<Diagnostic>,
    /// To ensure uniqueness of identifiers, we map every name to number of times
    /// it's used.
    permission_names: HashMap<String, i32>,
    query_names: HashMap<String, i32>,
    action_names: HashMap<String, i32>,
}

impl Program {
    /// Constructs a new program from the given source file, but it does not
    /// parse the data, you should call .parse() after the construction.
    pub fn new(source: Source) -> Program {
        Program {
            source,
            declarations: Vec::new(),
            type_space: TypeSpace::new_with_builtins(),
            permission_types: HashMap::new(),
            diagnostics: Vec::new(),
            permission_names: HashMap::new(),
            query_names: HashMap::new(),
            action_names: HashMap::new(),
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
        self.type_space = TypeSpace::new_with_builtins();
        self.permission_types.clear();
        self.diagnostics.clear();
        self.permission_names.clear();
        self.query_names.clear();
        self.action_names.clear();

        let mut parser = Parser::new(&self.source.content, 0);
        loop {
            match parser.parse_declaration() {
                Some(declaration) => match declaration {
                    Declaration::Type(type_declaration) => {
                        let cloned = Rc::clone(&type_declaration);
                        self.declarations.push(Declaration::Type(cloned));
                        if let Some(name) = &type_declaration.name {
                            if self.type_space.contains(&name.value) {
                                self.diagnostics.push(Diagnostic::name_already_in_use(name));
                            } else {
                                self.type_space.add_type(type_declaration);
                            }
                        }
                    }
                    Declaration::Permission(permission_declaration) => {
                        let cloned = Rc::clone(&permission_declaration);
                        self.declarations.push(Declaration::Permission(cloned));
                        if let Some(name) = &permission_declaration.name {
                            if self.permission_names.get_count(&name.value) > 0 {
                                self.diagnostics.push(Diagnostic::name_already_in_use(name));
                            }
                            self.permission_names.incr(String::from(&name.value));
                        }
                    }
                    Declaration::Query(query_declaration) => {
                        let cloned = Rc::clone(&query_declaration);
                        self.declarations.push(Declaration::Query(cloned));
                        if let Some(name) = &query_declaration.name {
                            if self.query_names.get_count(&name.value) > 0 {
                                self.diagnostics.push(Diagnostic::name_already_in_use(name));
                            }
                            self.query_names.incr(String::from(&name.value));
                        }
                    }
                    Declaration::Action(action_declaration) => {
                        let cloned = Rc::clone(&action_declaration);
                        self.declarations.push(Declaration::Action(cloned));
                        if let Some(name) = &action_declaration.name {
                            if self.action_names.get_count(&name.value) > 0 {
                                self.diagnostics.push(Diagnostic::name_already_in_use(name));
                            }
                            self.action_names.incr(String::from(&name.value));
                        }
                    }
                },
                None => break,
            }
        }

        for diagnostic in parser.diagnostics {
            self.report(diagnostic);
        }
    }

    pub fn verify(&mut self) {
        self.type_space.verify(&mut self.diagnostics);

        for declaration in &self.declarations {
            if let Declaration::Permission(permission_declaration) = declaration {
                let result =
                    permission_declaration.verify(&mut self.diagnostics, &mut self.type_space);
                if let Some(name) = &permission_declaration.name {
                    let mut parameter_types: Vec<Option<MarkusType>> =
                        Vec::with_capacity(permission_declaration.parameters.len());
                    for parameter in &permission_declaration.parameters {
                        parameter_types.push(if let Some(parameter_type_id) = &parameter.name {
                            let type_name = &parameter_type_id.value;
                            if let Some(parameter_type) = self.type_space.resolve_type(&type_name) {
                                Some(parameter_type.clone())
                            } else {
                                None
                            }
                        } else {
                            None
                        });
                    }
                    self.permission_types
                        .insert(String::from(&name.value), (parameter_types, result));
                }
            }
        }

        for declaration in &self.declarations {
            match declaration {
                Declaration::Query(query_declaration) => {
                    query_declaration.verify(
                        &mut self.diagnostics,
                        &mut self.type_space,
                        &self.permission_types,
                    );
                }
                Declaration::Action(action_declaration) => {
                    action_declaration.verify(
                        &mut self.diagnostics,
                        &mut self.type_space,
                        &self.permission_types,
                    );
                }
                _ => {}
            }
        }
    }
}
