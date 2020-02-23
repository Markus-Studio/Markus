use crate::parser::ast::{CallNode, ValueNode};
use crate::program::verify::VerifierContext;
use crate::program::{Diagnostic, MarkusType, MarkusTypeInfo};

impl CallNode {
    pub fn get_type(&self, ctx: &mut VerifierContext) -> MarkusType {
        get_type(self, ctx)
    }
}

#[inline(always)]
fn get_type(call: &CallNode, ctx: &mut VerifierContext) -> MarkusType {
    if None == call.callee_name {
        // An error is already reported about this pipeline not having a name.
        return MarkusType::new_union(Vec::with_capacity(0));
    }

    let name_id = call.callee_name.as_ref().unwrap();
    let callee_name = name_id.value.as_str();

    let result: Option<MarkusType> = match (callee_name, call.arguments.len()) {
        ("add", 2) | ("mul", 2) | ("sub", 2) | ("div", 2) => {
            match (&call.arguments[0], &call.arguments[1]) {
                (ValueNode::Query(_), _) | (ValueNode::Type(_), _) => {
                    ctx.diagnostics
                        .push(Diagnostic::unexpected_argument(&call.arguments[0]));
                    None
                }
                (_, ValueNode::Query(_)) | (_, ValueNode::Type(_)) => {
                    ctx.diagnostics
                        .push(Diagnostic::unexpected_argument(&call.arguments[1]));
                    None
                }
                (lhs, rhs) => mix_binary_numeric(ctx, lhs, rhs, callee_name == "div"),
            }
        }
        ("add", _) | ("mul", _) | ("sub", _) | ("div", _) => {
            ctx.diagnostics
                .push(Diagnostic::no_matching_signature(name_id));
            None
        }

        _ => {
            ctx.diagnostics.push(Diagnostic::unresolved_name(name_id));
            None
        }
    };

    match result {
        Some(t) => t,
        None => MarkusType::new_union(Vec::with_capacity(0)),
    }
}

#[inline(always)]
fn mix_binary_numeric(
    ctx: &mut VerifierContext,
    lhs: &ValueNode,
    rhs: &ValueNode,
    div: bool,
) -> Option<MarkusType> {
    let lhs_type = lhs.get_type(ctx);
    let rhs_type = rhs.get_type(ctx);

    let int_type = ctx.space.resolve_type("%int").unwrap();
    let float_type = ctx.space.resolve_type("%float").unwrap();
    if !(lhs_type.is(ctx.space, int_type) || lhs_type.is(ctx.space, float_type)) {
        ctx.diagnostics.push(Diagnostic::mismatched_types(
            lhs_type.to_string(ctx.space),
            String::from("(%int | %float)"),
            rhs.get_location(),
        ));
        return None;
    }

    Some(get_binary_type(ctx, &lhs_type, &rhs_type, div))
}

#[inline(always)]
fn get_binary_type(
    ctx: &mut VerifierContext,
    lhs_type: &MarkusType,
    rhs_type: &MarkusType,
    div: bool,
) -> MarkusType {
    if div {
        return ctx.space.resolve_type("%float").unwrap().clone();
    }

    match (&lhs_type.type_info, &rhs_type.type_info) {
        (
            MarkusTypeInfo::Atomic { name: lhs_name, .. },
            MarkusTypeInfo::Atomic { name: rhs_name, .. },
        ) => ctx
            .space
            .resolve_type(match (lhs_name as &str, rhs_name as &str) {
                ("f64", _) | (_, "f64") => "f64",
                ("f32", _) | (_, "f32") => "%float",
                (_, _) => "%int",
            })
            .unwrap()
            .clone(),

        (MarkusTypeInfo::Union { members, .. }, _) if members.len() == 1 => {
            let ids: Vec<&u32> = members.iter().collect();
            let id = *ids[0];
            let lhs = ctx.space.resolve_type_by_id(id).unwrap().clone();
            get_binary_type(ctx, &lhs, rhs_type, div)
        }

        (_, MarkusTypeInfo::Union { members, .. }) if members.len() == 1 => {
            let ids: Vec<&u32> = members.iter().collect();
            let id = *ids[0];
            let rhs = ctx.space.resolve_type_by_id(id).unwrap().clone();
            get_binary_type(ctx, lhs_type, &rhs, div)
        }

        (MarkusTypeInfo::Atomic { name, .. }, _) | (_, MarkusTypeInfo::Atomic { name, .. }) => ctx
            .space
            .resolve_type(match name as &str {
                "f64" => "f64",
                "f32" => "%float",
                _ => "%int",
            })
            .unwrap()
            .clone(),

        (
            MarkusTypeInfo::OneOf { name: lhs_name, .. },
            MarkusTypeInfo::OneOf { name: rhs_name, .. },
        ) => ctx
            .space
            .resolve_type(match (lhs_name as &str, rhs_name as &str) {
                ("%number", _) | (_, "%number") => "%number",
                ("%float", _) | (_, "%float") => "%float",
                (_, _) => "%int",
            })
            .unwrap()
            .clone(),

        (_, _) => unimplemented!(),
    }
}
