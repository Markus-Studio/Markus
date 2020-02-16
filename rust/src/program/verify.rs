#![allow(dead_code)]
use crate::parser::ast::{CallNode, IntLiteralNode, QueryDeclarationNode};
use crate::parser::ast::{QueryNode, ValueNode, VariableReferenceNode};
use crate::parser::Span;
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

impl VariableReferenceNode {
    pub fn get_type(
        &self,
        diagnostics: &mut Vec<Diagnostic>,
        ctx: &mut QueryValidatorContext,
    ) -> MarkusType {
        match self {
            VariableReferenceNode::Current => {
                let current = ctx.get_current();
                current.with_dimension(current.dimension - 1)
            }
            VariableReferenceNode::Internal(id) | VariableReferenceNode::Variable(id) => {
                if let Some(variable_type) = ctx.variables.get(&id.value) {
                    variable_type.clone()
                } else {
                    diagnostics.push(Diagnostic::unresolved_name(&id));
                    MarkusType::new_union(Vec::with_capacity(0))
                }
            }
        }
    }
}

impl ValueNode {
    /// Computes and returns type of this value.
    pub fn get_type(
        &self,
        diagnostics: &mut Vec<Diagnostic>,
        ctx: &mut QueryValidatorContext,
    ) -> MarkusType {
        match self {
            ValueNode::Int(IntLiteralNode { neg, .. }) => {
                if *neg {
                    ctx.space.resolve_type("%neg-int").unwrap().clone()
                } else {
                    ctx.space.resolve_type("%int").unwrap().clone()
                }
            }
            ValueNode::Float(_) => ctx.space.resolve_type("%float").unwrap().clone(),
            ValueNode::Boolean(_) => ctx.space.resolve_type("bool").unwrap().clone(),
            ValueNode::Null(_) => ctx.space.resolve_type("null").unwrap().clone(),
            ValueNode::String(_) => ctx.space.resolve_type("string").unwrap().clone(),
            ValueNode::Access(access) => {
                let uri: Vec<&str> = access.parts.iter().map(|p| &*p.value).collect();
                let base_type = access.base.get_type(diagnostics, ctx);
                match base_type.query(ctx.space, &uri) {
                    Some(data_type) => data_type,
                    _ => {
                        let type_str = base_type.to_string(ctx.space);
                        diagnostics.push(Diagnostic::field_not_found(
                            type_str,
                            uri,
                            access.location,
                        ));
                        MarkusType::new_union(Vec::with_capacity(0))
                    }
                }
            }
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
            // TODO(qti3e) Still check type of the non-call/query arguments.
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
                    match ctx.space.resolve_type(&type_reference.name.value) {
                        Some(arg) => {
                            let filtered_type = ctx.get_current().filter(ctx.space, arg);
                            ctx.set_current(filtered_type);
                        }
                        _ => {
                            diagnostics.push(Diagnostic::unresolved_name(&type_reference.name));
                        }
                    }
                }
                _ => {
                    diagnostics.push(Diagnostic::expected_argument_type(&self.arguments[0]));
                }
            },
            ("is", _) => diagnostics.push(Diagnostic::no_matching_signature(name_id)),

            ("neq", 2) | ("eq", 2) => match (&self.arguments[0], &self.arguments[1]) {
                (ValueNode::Query(_), _) | (ValueNode::Type(_), _) => {
                    diagnostics.push(Diagnostic::unexpected_argument(&self.arguments[0]));
                }
                (_, ValueNode::Query(_)) | (_, ValueNode::Type(_)) => {
                    diagnostics.push(Diagnostic::unexpected_argument(&self.arguments[1]));
                }
                (lhs, rhs) => {
                    let lhs_type = lhs.get_type(diagnostics, ctx);
                    let rhs_type = rhs.get_type(diagnostics, ctx);
                    if !(lhs_type.is(ctx.space, &rhs_type) || rhs_type.is(ctx.space, &lhs_type)) {
                        diagnostics.push(Diagnostic::mismatched_types(
                            lhs_type.to_string(ctx.space),
                            rhs_type.to_string(ctx.space),
                            rhs.get_location(),
                        ))
                    }
                }
            },
            ("neq", _) | ("eq", _) => diagnostics.push(Diagnostic::no_matching_signature(name_id)),

            ("lte", 2) | ("lt", 2) | ("gte", 2) | ("gt", 2) => {
                match (&self.arguments[0], &self.arguments[1]) {
                    (ValueNode::Query(_), _) | (ValueNode::Type(_), _) => {
                        diagnostics.push(Diagnostic::unexpected_argument(&self.arguments[0]));
                    }
                    (_, ValueNode::Query(_)) | (_, ValueNode::Type(_)) => {
                        diagnostics.push(Diagnostic::unexpected_argument(&self.arguments[1]));
                    }
                    (lhs, rhs) => {
                        let lhs_type = lhs.get_type(diagnostics, ctx);
                        let rhs_type = rhs.get_type(diagnostics, ctx);
                        if !(lhs_type.is(ctx.space, &rhs_type) || rhs_type.is(ctx.space, &lhs_type))
                        {
                            diagnostics.push(Diagnostic::mismatched_types(
                                lhs_type.to_string(ctx.space),
                                rhs_type.to_string(ctx.space),
                                rhs.get_location(),
                            ))
                        }
                        let int_type = ctx.space.resolve_type("%int").unwrap();
                        let float_type = ctx.space.resolve_type("%float").unwrap();
                        if !(lhs_type.is(ctx.space, int_type) || lhs_type.is(ctx.space, float_type))
                        {
                            diagnostics.push(Diagnostic::mismatched_types(
                                lhs_type.to_string(ctx.space),
                                String::from("(%int | %float)"),
                                rhs.get_location(),
                            ))
                        }
                    }
                }
            }
            ("lte", _) | ("lt", _) | ("gte", _) | ("gt", _) => {
                diagnostics.push(Diagnostic::no_matching_signature(name_id))
            }

            ("sum", 0) => {
                let value_type = ctx.get_current().clone();
                sum_pipeline(
                    diagnostics,
                    ctx,
                    &value_type,
                    self.arguments[0].get_location(),
                );
            }
            ("sum", 1) => match &self.arguments[0] {
                ValueNode::Access(access_node) => match access_node.base {
                    VariableReferenceNode::Current => {
                        let field_type = self.arguments[0].get_type(diagnostics, ctx);
                        sum_pipeline(
                            diagnostics,
                            ctx,
                            &field_type,
                            self.arguments[0].get_location(),
                        );
                    }
                    _ => {
                        diagnostics.push(Diagnostic::expected_argument_field(&self.arguments[0]));
                    }
                },
                _ => {
                    diagnostics.push(Diagnostic::expected_argument_field(&self.arguments[0]));
                }
            },
            ("sum", _) => diagnostics.push(Diagnostic::no_matching_signature(name_id)),

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
        println!("T {}", ctx.get_current().to_string(ctx.space));
        for pipeline in &self.pipelines {
            pipeline.apply_pipeline_changes(diagnostics, ctx);
            println!("T {}", ctx.get_current().to_string(ctx.space));
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
            space,
            branches: Vec::new(),
            current: vec![space.get_query_input_type()],
            variables: HashMap::new(),
        };

        let null_id = space.resolve_type("null").unwrap().get_id();
        for parameter in &self.parameters {
            if None == parameter.name || None == parameter.type_name {
                continue;
            }

            match (parameter.name.as_ref(), parameter.type_name.as_ref()) {
                (Some(parameter_name), None) => {
                    if context.variables.contains_key(&parameter_name.value) {
                        diagnostics.push(Diagnostic::name_already_in_use(&parameter_name));
                    }
                }
                (None, _) => {}
                (Some(parameter_name), Some(type_name)) => {
                    let name = String::from(&parameter_name.value);

                    if context.variables.contains_key(&name) {
                        diagnostics.push(Diagnostic::name_already_in_use(&parameter_name));
                    }

                    if let Some(parameter_type) = space.resolve_type(&type_name.value) {
                        if parameter.optional {
                            let type_id = parameter_type.get_id();
                            context
                                .variables
                                .insert(name, MarkusType::new_union(vec![null_id, type_id]));
                        } else {
                            context.variables.insert(name, parameter_type.clone());
                        }
                    } else {
                        diagnostics.push(Diagnostic::unresolved_name(&type_name));
                    }
                }
            }
        }

        self.query.get_type(diagnostics, &mut context);
    }
}

#[inline(always)]
fn sum_pipeline(
    diagnostics: &mut Vec<Diagnostic>,
    ctx: &mut QueryValidatorContext,
    field_type: &MarkusType,
    location: Span,
) {
    let unsigned_type = ctx.space.resolve_type("%unsigned-int").unwrap();
    if field_type.is(ctx.space, unsigned_type) {
        let u64_type = ctx.space.resolve_type("u64").unwrap();
        ctx.set_current(u64_type.clone());
        return;
    }

    let int_type = ctx.space.resolve_type("%int").unwrap();
    if field_type.is(ctx.space, int_type) {
        let i64_type = ctx.space.resolve_type("i64").unwrap();
        ctx.set_current(i64_type.clone());
        return;
    }

    let float_type = ctx.space.resolve_type("%float").unwrap();
    if field_type.is(ctx.space, float_type) {
        let f64_type = ctx.space.resolve_type("f64").unwrap();
        ctx.set_current(f64_type.clone());
        return;
    }

    diagnostics.push(Diagnostic::mismatched_types(
        field_type.to_string(ctx.space),
        String::from("numeric"),
        location,
    ))
}
