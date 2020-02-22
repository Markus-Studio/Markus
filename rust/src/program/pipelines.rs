use crate::parser::ast::{CallNode, ValueNode, VariableReferenceNode};
use crate::parser::Span;
use crate::program::verify::VerifierContext;
use crate::program::{Diagnostic, MarkusType};

impl CallNode {
    pub fn apply_pipeline_changes(&self, ctx: &mut VerifierContext) {
        apply_pipeline_changes(self, ctx, ctx.only_filters, false);
        let current = ctx.get_current();
    }
}

#[inline(always)]
fn apply_pipeline_changes(
    call: &CallNode,
    ctx: &mut VerifierContext,
    only_filters: bool,
    neg: bool,
) {
    if None == call.callee_name {
        // An error is already reported about this pipeline not having a name.
        return;
    }

    let name_id = call.callee_name.as_ref().unwrap();
    let callee_name = name_id.value.as_str();

    match (callee_name, call.arguments.len()) {
        ("or", _) => {
            ctx.branch_in();
            for argument in &call.arguments {
                match argument {
                    ValueNode::Call(call) => {
                        ctx.path_enter();
                        apply_pipeline_changes(call, ctx, true, neg);
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
            for argument in &call.arguments {
                match argument {
                    ValueNode::Call(call) => {
                        call.apply_pipeline_changes(ctx);
                        apply_pipeline_changes(call, ctx, true, neg);
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

        ("neg", 1) => match &call.arguments[0] {
            ValueNode::Call(call) => apply_pipeline_changes(call, ctx, true, !neg),
            _ => ctx
                .diagnostics
                .push(Diagnostic::expected_argument_pipeline(&call.arguments[0])),
        },

        ("is", 1) => match &call.arguments[0] {
            ValueNode::Type(type_reference) => {
                match ctx.space.resolve_type(&type_reference.name.value) {
                    Some(arg) => {
                        let filtered_type = ctx.get_current().filter(ctx.space, arg, neg);
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
                    .push(Diagnostic::expected_argument_type(&call.arguments[0]));
            }
        },
        ("is", _) => ctx
            .diagnostics
            .push(Diagnostic::no_matching_signature(name_id)),

        ("neq", 2) | ("eq", 2) => match (&call.arguments[0], &call.arguments[1]) {
            (ValueNode::Query(_), _) | (ValueNode::Type(_), _) => {
                ctx.diagnostics
                    .push(Diagnostic::unexpected_argument(&call.arguments[0]));
            }
            (_, ValueNode::Query(_)) | (_, ValueNode::Type(_)) => {
                ctx.diagnostics
                    .push(Diagnostic::unexpected_argument(&call.arguments[1]));
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
            match (&call.arguments[0], &call.arguments[1]) {
                (ValueNode::Query(_), _) | (ValueNode::Type(_), _) => {
                    ctx.diagnostics
                        .push(Diagnostic::unexpected_argument(&call.arguments[0]));
                }
                (_, ValueNode::Query(_)) | (_, ValueNode::Type(_)) => {
                    ctx.diagnostics
                        .push(Diagnostic::unexpected_argument(&call.arguments[1]));
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
                    let int_type = ctx.space.resolve_type("%int").unwrap();
                    let float_type = ctx.space.resolve_type("%float").unwrap();
                    if !(lhs_type.is(ctx.space, int_type) || lhs_type.is(ctx.space, float_type)) {
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

        ("sum", _) if only_filters => ctx.diagnostics.push(Diagnostic::unresolved_name(name_id)),
        ("sum", 0) => {
            let value_type = ctx.get_current().clone();
            sum_pipeline(ctx, &value_type, call.arguments[0].get_location());
        }
        ("sum", 1) => match &call.arguments[0] {
            ValueNode::Access(access_node) => match access_node.base {
                VariableReferenceNode::Current => {
                    let field_type = call.arguments[0].get_type(ctx);
                    sum_pipeline(ctx, &field_type, call.arguments[0].get_location());
                }
                _ => {
                    ctx.diagnostics
                        .push(Diagnostic::expected_argument_field(&call.arguments[0]));
                }
            },
            _ => {
                ctx.diagnostics
                    .push(Diagnostic::expected_argument_field(&call.arguments[0]));
            }
        },
        ("sum", _) => ctx
            .diagnostics
            .push(Diagnostic::no_matching_signature(name_id)),

        ("avg", _) if only_filters => ctx.diagnostics.push(Diagnostic::unresolved_name(name_id)),
        ("avg", 0) => {
            let value_type = ctx.get_current().clone();
            avg_pipeline(ctx, &value_type, call.arguments[0].get_location());
        }
        ("avg", 1) => match &call.arguments[0] {
            ValueNode::Access(access_node) => match access_node.base {
                VariableReferenceNode::Current => {
                    let field_type = call.arguments[0].get_type(ctx);
                    avg_pipeline(ctx, &field_type, call.arguments[0].get_location());
                }
                _ => {
                    ctx.diagnostics
                        .push(Diagnostic::expected_argument_field(&call.arguments[0]));
                }
            },
            _ => {
                ctx.diagnostics
                    .push(Diagnostic::expected_argument_field(&call.arguments[0]));
            }
        },
        ("avg", _) => ctx
            .diagnostics
            .push(Diagnostic::no_matching_signature(name_id)),

        ("min", _) if only_filters => ctx.diagnostics.push(Diagnostic::unresolved_name(name_id)),
        ("min", 0) => {
            let value_type = ctx.get_current().clone();
            min_pipeline(ctx, &value_type, call.arguments[0].get_location());
        }
        ("min", 1) => match &call.arguments[0] {
            ValueNode::Access(access_node) => match access_node.base {
                VariableReferenceNode::Current => {
                    let field_type = call.arguments[0].get_type(ctx);
                    min_pipeline(ctx, &field_type, call.arguments[0].get_location());
                }
                _ => {
                    ctx.diagnostics
                        .push(Diagnostic::expected_argument_field(&call.arguments[0]));
                }
            },
            _ => {
                ctx.diagnostics
                    .push(Diagnostic::expected_argument_field(&call.arguments[0]));
            }
        },
        ("min", _) => ctx
            .diagnostics
            .push(Diagnostic::no_matching_signature(name_id)),

        ("max", _) if only_filters => ctx.diagnostics.push(Diagnostic::unresolved_name(name_id)),
        ("max", 0) => {
            let value_type = ctx.get_current().clone();
            min_pipeline(ctx, &value_type, call.arguments[0].get_location());
        }
        ("max", 1) => match &call.arguments[0] {
            ValueNode::Access(access_node) => match access_node.base {
                VariableReferenceNode::Current => {
                    let field_type = call.arguments[0].get_type(ctx);
                    min_pipeline(ctx, &field_type, call.arguments[0].get_location());
                }
                _ => {
                    ctx.diagnostics
                        .push(Diagnostic::expected_argument_field(&call.arguments[0]));
                }
            },
            _ => {
                ctx.diagnostics
                    .push(Diagnostic::expected_argument_field(&call.arguments[0]));
            }
        },
        ("max", _) => ctx
            .diagnostics
            .push(Diagnostic::no_matching_signature(name_id)),

        ("count", _) if only_filters => ctx.diagnostics.push(Diagnostic::unresolved_name(name_id)),
        ("count", 0) => {
            let value_type = ctx.get_current().clone();
            count_pipeline(ctx, &value_type, call.arguments[0].get_location());
        }
        ("count", _) => ctx
            .diagnostics
            .push(Diagnostic::no_matching_signature(name_id)),

        ("groupBy", _) if only_filters => {
            ctx.diagnostics.push(Diagnostic::unresolved_name(name_id))
        }
        ("groupBy", 1) => match &call.arguments[0] {
            ValueNode::Access(access_node) => match access_node.base {
                VariableReferenceNode::Current => {
                    let field_type = call.arguments[0].get_type(ctx);
                    let inner_type = ctx.get_current().clone();
                    let map = ctx
                        .space
                        .define_map(field_type, inner_type)
                        .with_dimension(1);
                    ctx.set_current(map);
                }
                _ => {
                    ctx.diagnostics
                        .push(Diagnostic::expected_argument_field(&call.arguments[0]));
                }
            },
            _ => {
                ctx.diagnostics
                    .push(Diagnostic::expected_argument_field(&call.arguments[0]));
            }
        },
        ("groupBy", 2) => match (&call.arguments[0], &call.arguments[1]) {
            (ValueNode::Access(access_node), ValueNode::Query(query)) => match access_node.base {
                VariableReferenceNode::Current => {
                    let field_type = call.arguments[0].get_type(ctx);
                    ctx.branch_in();
                    ctx.path_enter();
                    query.get_type(ctx);
                    ctx.path_exit();
                    let inner_type = ctx.branch_pop();
                    let map = ctx
                        .space
                        .define_map(field_type, inner_type)
                        .with_dimension(1);
                    ctx.set_current(map);
                }
                _ => {
                    ctx.diagnostics
                        .push(Diagnostic::expected_argument_field(&call.arguments[0]));
                }
            },
            (ValueNode::Access(_), _) => {
                ctx.diagnostics
                    .push(Diagnostic::expected_argument_field(&call.arguments[1]));
            }
            _ => {
                ctx.diagnostics
                    .push(Diagnostic::expected_argument_field(&call.arguments[0]));
            }
        },
        ("groupBy", _) => ctx
            .diagnostics
            .push(Diagnostic::no_matching_signature(name_id)),

        _ => ctx.diagnostics.push(Diagnostic::unresolved_name(name_id)),
    }
}

#[inline(always)]
fn sum_pipeline(ctx: &mut VerifierContext, field_type: &MarkusType, location: Span) {
    let unsigned_type = ctx.space.resolve_type("%unsigned-int").unwrap();
    if field_type.is(ctx.space, unsigned_type) {
        let u64_type = ctx.space.resolve_type("u64").unwrap().clone();
        ctx.set_current(u64_type);
        return;
    }

    let int_type = ctx.space.resolve_type("%int").unwrap();
    if field_type.is(ctx.space, int_type) {
        let i64_type = ctx.space.resolve_type("i64").unwrap().clone();
        ctx.set_current(i64_type);
        return;
    }

    let float_type = ctx.space.resolve_type("%float").unwrap();
    if field_type.is(ctx.space, float_type) {
        let f64_type = ctx.space.resolve_type("f64").unwrap().clone();
        ctx.set_current(f64_type);
        return;
    }

    ctx.diagnostics.push(Diagnostic::mismatched_types(
        field_type.to_string(ctx.space),
        String::from("numeric"),
        location,
    ))
}

#[inline(always)]
fn avg_pipeline(ctx: &mut VerifierContext, field_type: &MarkusType, location: Span) {
    let number = ctx.space.resolve_type("%number").unwrap();

    if field_type.is(ctx.space, number) {
        let f64_type = ctx.space.resolve_type("f64").unwrap().clone();
        ctx.set_current(f64_type);
        return;
    }

    ctx.diagnostics.push(Diagnostic::mismatched_types(
        field_type.to_string(ctx.space),
        String::from("numeric"),
        location,
    ));
}

#[inline(always)]
fn min_pipeline(ctx: &mut VerifierContext, field_type: &MarkusType, location: Span) {
    let number = ctx.space.resolve_type("%number").unwrap();

    if field_type.is(ctx.space, number) {
        ctx.set_current(field_type.clone());
        return;
    }

    ctx.diagnostics.push(Diagnostic::mismatched_types(
        field_type.to_string(ctx.space),
        String::from("numeric"),
        location,
    ));
}

#[inline(always)]
fn count_pipeline(ctx: &mut VerifierContext, field_type: &MarkusType, location: Span) {
    let number = ctx.space.resolve_type("%number").unwrap();

    if field_type.is(ctx.space, number) {
        let u32_type = ctx.space.resolve_type("u32").unwrap().clone();
        ctx.set_current(u32_type);
        return;
    }

    ctx.diagnostics.push(Diagnostic::mismatched_types(
        field_type.to_string(ctx.space),
        String::from("numeric"),
        location,
    ));
}
