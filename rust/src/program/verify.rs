use crate::parser::ast::PermissionDeclarationNode;
use crate::parser::ast::{ActionDeclarationNode, QueryDeclarationNode};
use crate::program::{Diagnostic, MarkusType, TypeSpace};
use std::collections::HashMap;

pub struct VerifierContext<'a> {
    pub space: &'a TypeSpace,
    pub diagnostics: &'a mut Vec<Diagnostic>,
    pub symbol_table: HashMap<String, MarkusType>,
    branches: Vec<Vec<MarkusType>>,
    current: Vec<MarkusType>,
}

impl<'a> VerifierContext<'a> {
    #[inline]
    pub fn branch_in(&mut self) {
        self.branches.push(Vec::new());
    }

    #[inline]
    pub fn branch_out(&mut self) {
        let types = self.branches.pop().unwrap();
        if types.len() > 0 {
            let union = MarkusType::create_union_from(types);
            self.set_current(union);
        }
    }

    #[inline]
    pub fn path_enter(&mut self) {
        let current_type = self.get_current().clone();
        self.current.push(current_type);
    }

    #[inline]
    pub fn path_exit(&mut self) {
        self.branches
            .last_mut()
            .unwrap()
            .push(self.current.pop().unwrap());
    }

    #[inline]
    pub fn set_current(&mut self, current: MarkusType) {
        let last_index = self.current.len() - 1;
        self.current[last_index] = current;
    }

    #[inline]
    pub fn get_current(&self) -> &MarkusType {
        self.current.last().unwrap()
    }

    #[inline]
    pub fn resolve_variable(&self, name: &str) -> Option<&MarkusType> {
        self.symbol_table.get(name)
    }
}

impl PermissionDeclarationNode {
    pub fn verify<'a>(
        &self,
        diagnostics: &mut Vec<Diagnostic>,
        space: &'a TypeSpace,
    ) -> Option<MarkusType> {
        None
    }
}

impl QueryDeclarationNode {
    pub fn verify<'a>(&self, diagnostics: &mut Vec<Diagnostic>, space: &'a TypeSpace) {
        let mut ctx = VerifierContext {
            space,
            diagnostics,
            branches: Vec::new(),
            current: vec![space.get_query_input_type()],
            symbol_table: HashMap::new(),
        };

        let null_id = space.resolve_type("null").unwrap().get_id();
        for parameter in &self.parameters {
            if None == parameter.name || None == parameter.type_name {
                continue;
            }

            match (parameter.name.as_ref(), parameter.type_name.as_ref()) {
                (Some(parameter_name), None) => {
                    if ctx.symbol_table.contains_key(&parameter_name.value) {
                        ctx.diagnostics
                            .push(Diagnostic::name_already_in_use(&parameter_name));
                    }
                }
                (None, _) => {}
                (Some(parameter_name), Some(type_name)) => {
                    let name = String::from(&parameter_name.value);

                    if ctx.symbol_table.contains_key(&name) {
                        ctx.diagnostics
                            .push(Diagnostic::name_already_in_use(&parameter_name));
                    }

                    if let Some(parameter_type) = space.resolve_type(&type_name.value) {
                        if parameter.optional {
                            let type_id = parameter_type.get_id();
                            ctx.symbol_table
                                .insert(name, MarkusType::new_union(vec![null_id, type_id]));
                        } else {
                            ctx.symbol_table.insert(name, parameter_type.clone());
                        }
                    } else {
                        ctx.diagnostics
                            .push(Diagnostic::unresolved_name(&type_name));
                    }
                }
            }
        }

        self.query.get_type(&mut ctx);
    }
}

impl ActionDeclarationNode {
    pub fn verify<'a>(&self, diagnostics: &mut Vec<Diagnostic>, space: &'a TypeSpace) {}
}
