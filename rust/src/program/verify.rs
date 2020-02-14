#![allow(dead_code)]
use crate::parser::ast::{CallNode, IntLiteralNode, QueryDeclarationNode, QueryNode, ValueNode};
use crate::program::{Diagnostic, MarkusType, TypeSpace};
use std::collections::HashMap;

#[derive(Clone)]
pub struct QueryValidatorContext<'a> {
    space: &'a TypeSpace,
    branches: Vec<Vec<MarkusType>>,
    current: Vec<MarkusType>,
    variables: HashMap<String, MarkusType>,
}

impl<'a> QueryValidatorContext<'a> {
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
        self.variables.get(name)
    }
}

impl ValueNode {
    /// Computes and returns type of this value.
    pub fn get_type(&self, space: &TypeSpace) -> Option<MarkusType> {
        match self {
            ValueNode::Int(IntLiteralNode { neg, .. }) => {
                if *neg {
                    Some(space.resolve_type("%neg-int").unwrap().clone())
                } else {
                    Some(space.resolve_type("%int").unwrap().clone())
                }
            }
            ValueNode::Float(_) => Some(space.resolve_type("%float").unwrap().clone()),
            ValueNode::Boolean(_) => Some(space.resolve_type("bool").unwrap().clone()),
            _ => panic!("Not implemented."),
        }
    }
}

impl CallNode {
    #[inline]
    pub fn apply_pipeline_changes(
        &self,
        diagnostics: &mut Vec<Diagnostic>,
        ctx: &mut QueryValidatorContext,
    ) {
        if None == self.callee_name {
            // An error is already reported about this pipeline not having a name.
            // TODO(qti3e) Still check type of non-call the arguments.
            return;
        }

        let name_id = self.callee_name.as_ref().unwrap();
        let callee_name = name_id.value.as_str();

        match (callee_name, self.arguments.len()) {
            ("or", _) => {
                ctx.branch_in();
                for argument in &self.arguments {
                    match argument {
                        ValueNode::Call(call) => {
                            ctx.path_enter();
                            call.apply_pipeline_changes(diagnostics, ctx);
                            if ctx.get_current().is_nil() {
                                diagnostics.push(Diagnostic::reached_nil(call));
                                break;
                            }
                            ctx.path_exit();
                        }
                        _ => {
                            diagnostics.push(Diagnostic::expected_argument_pipeline(argument));
                        }
                    }
                }
                ctx.branch_out();
            }
            ("and", _) => {
                for argument in &self.arguments {
                    match argument {
                        ValueNode::Call(call) => {
                            call.apply_pipeline_changes(diagnostics, ctx);
                            if ctx.get_current().is_nil() {
                                diagnostics.push(Diagnostic::reached_nil(call));
                                break;
                            }
                        }
                        _ => {
                            diagnostics.push(Diagnostic::expected_argument_pipeline(argument));
                        }
                    }
                }
            }
            ("is", 1) => match &self.arguments[0] {
                ValueNode::Type(type_reference) => {
                    //
                }
                _ => {
                    // Report error, unexpected argument.
                }
            },
            ("is", _) => diagnostics.push(Diagnostic::no_matching_signature(name_id)),
            _ => diagnostics.push(Diagnostic::unresolved_name(name_id)),
        }
    }
}

impl QueryNode {
    pub fn get_type(
        &self,
        diagnostics: &mut Vec<Diagnostic>,
        ctx: &mut QueryValidatorContext,
    ) -> MarkusType {
        for pipeline in &self.pipelines {
            pipeline.apply_pipeline_changes(diagnostics, ctx);
            if ctx.get_current().is_nil() {
                diagnostics.push(Diagnostic::reached_nil(pipeline));
                break;
            }
        }
        ctx.get_current().clone()
    }
}

impl QueryDeclarationNode {
    pub fn verify<'a>(&self, diagnostics: &mut Vec<Diagnostic>, space: &'a TypeSpace) {
        let mut context = QueryValidatorContext {
            space: space,
            branches: Vec::new(),
            current: vec![space.get_query_input_type()],
            variables: HashMap::new(),
        };

        self.query.get_type(diagnostics, &mut context);
    }
}
