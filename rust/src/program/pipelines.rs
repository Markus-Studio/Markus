use crate::parser::ast::{CallNode, ValueNode, VariableReferenceNode};
use crate::parser::Span;
use crate::program::verify::VerifierContext;
use crate::program::{Diagnostic, MarkusType};

impl CallNode {
    pub fn apply_pipeline_changes(&self, ctx: &mut VerifierContext) {
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
                            call.apply_pipeline_changes(ctx);
                            if ctx.get_current().is_nil() {
                                ctx.diagnostics.push(Diagnostic::reached_nil(call));
                                break;
                            }
                            ctx.path_exit();
                        }
                        _ => {
                            ctx.diagnostics
                                .push(Diagnostic::expected_argument_pipeline(argument));
                        }
                    }
                }
                ctx.branch_out();
            }

            ("and", _) => {
                for argument in &self.arguments {
                    match argument {
                        ValueNode::Call(call) => {
                            call.apply_pipeline_changes(ctx);
                            if ctx.get_current().is_nil() {
                                ctx.diagnostics.push(Diagnostic::reached_nil(call));
                                break;
                            }
                        }
                        _ => {
                            ctx.diagnostics
                                .push(Diagnostic::expected_argument_pipeline(argument));
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
                            ctx.diagnostics
                                .push(Diagnostic::unresolved_name(&type_reference.name));
                        }
                    }
                }
                _ => {
                    ctx.diagnostics
                        .push(Diagnostic::expected_argument_type(&self.arguments[0]));
                }
            },
            ("is", _) => ctx
                .diagnostics
                .push(Diagnostic::no_matching_signature(name_id)),

            ("neq", 2) | ("eq", 2) => match (&self.arguments[0], &self.arguments[1]) {
                (ValueNode::Query(_), _) | (ValueNode::Type(_), _) => {
                    ctx.diagnostics
                        .push(Diagnostic::unexpected_argument(&self.arguments[0]));
                }
                (_, ValueNode::Query(_)) | (_, ValueNode::Type(_)) => {
                    ctx.diagnostics
                        .push(Diagnostic::unexpected_argument(&self.arguments[1]));
                }
                (lhs, rhs) => {
                    let lhs_type = lhs.get_type(ctx);
                    let rhs_type = rhs.get_type(ctx);
                    if !(lhs_type.is(ctx.space, &rhs_type) || rhs_type.is(ctx.space, &lhs_type)) {
                        ctx.diagnostics.push(Diagnostic::mismatched_types(
                            lhs_type.to_string(ctx.space),
                            rhs_type.to_string(ctx.space),
                            rhs.get_location(),
                        ))
                    }
                }
            },
            ("neq", _) | ("eq", _) => ctx
                .diagnostics
                .push(Diagnostic::no_matching_signature(name_id)),

            ("lte", 2) | ("lt", 2) | ("gte", 2) | ("gt", 2) => {
                match (&self.arguments[0], &self.arguments[1]) {
                    (ValueNode::Query(_), _) | (ValueNode::Type(_), _) => {
                        ctx.diagnostics
                            .push(Diagnostic::unexpected_argument(&self.arguments[0]));
                    }
                    (_, ValueNode::Query(_)) | (_, ValueNode::Type(_)) => {
                        ctx.diagnostics
                            .push(Diagnostic::unexpected_argument(&self.arguments[1]));
                    }
                    (lhs, rhs) => {
                        let lhs_type = lhs.get_type(ctx);
                        let rhs_type = rhs.get_type(ctx);
                        if !(lhs_type.is(ctx.space, &rhs_type) || rhs_type.is(ctx.space, &lhs_type))
                        {
                            ctx.diagnostics.push(Diagnostic::mismatched_types(
                                lhs_type.to_string(ctx.space),
                                rhs_type.to_string(ctx.space),
                                rhs.get_location(),
                            ))
                        }
                        let int_type = ctx.space.resolve_type("%int").unwrap();
                        let float_type = ctx.space.resolve_type("%float").unwrap();
                        if !(lhs_type.is(ctx.space, int_type) || lhs_type.is(ctx.space, float_type))
                        {
                            ctx.diagnostics.push(Diagnostic::mismatched_types(
                                lhs_type.to_string(ctx.space),
                                String::from("(%int | %float)"),
                                rhs.get_location(),
                            ))
                        }
                    }
                }
            }
            ("lte", _) | ("lt", _) | ("gte", _) | ("gt", _) => ctx
                .diagnostics
                .push(Diagnostic::no_matching_signature(name_id)),

            ("sum", 0) => {
                let value_type = ctx.get_current().clone();
                sum_pipeline(ctx, &value_type, self.arguments[0].get_location());
            }
            ("sum", 1) => match &self.arguments[0] {
                ValueNode::Access(access_node) => match access_node.base {
                    VariableReferenceNode::Current => {
                        let field_type = self.arguments[0].get_type(ctx);
                        sum_pipeline(ctx, &field_type, self.arguments[0].get_location());
                    }
                    _ => {
                        ctx.diagnostics
                            .push(Diagnostic::expected_argument_field(&self.arguments[0]));
                    }
                },
                _ => {
                    ctx.diagnostics
                        .push(Diagnostic::expected_argument_field(&self.arguments[0]));
                }
            },
            ("sum", _) => ctx
                .diagnostics
                .push(Diagnostic::no_matching_signature(name_id)),

            _ => ctx.diagnostics.push(Diagnostic::unresolved_name(name_id)),
        }
    }
}

#[inline(always)]
fn sum_pipeline(ctx: &mut VerifierContext, field_type: &MarkusType, location: Span) {
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

    ctx.diagnostics.push(Diagnostic::mismatched_types(
        field_type.to_string(ctx.space),
        String::from("numeric"),
        location,
    ))
}