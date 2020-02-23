use crate::context::Context;
use crate::parser::ast::{CallNode, ValueNode};
use crate::program::{Diagnostic, MarkusType, MarkusTypeInfo};

impl CallNode {
    pub fn get_type(&self, ctx: &mut Context) -> MarkusType {
        get_type(self, ctx)
    }
}

#[inline(always)]
fn get_type(call: &CallNode, ctx: &mut Context) -> MarkusType {
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

        ("floor", 1) | ("ceil", 1) | ("round", 1) => match &call.arguments[0] {
            ValueNode::Query(_) | ValueNode::Type(_) => {
                ctx.diagnostics
                    .push(Diagnostic::unexpected_argument(&call.arguments[0]));
                None
            }
            value => {
                let value_type = value.get_type(ctx);
                let number_type = ctx.space.resolve_type("%number").unwrap();
                if !value_type.is(ctx.space, number_type) {
                    ctx.diagnostics.push(Diagnostic::mismatched_types(
                        value_type.to_string(ctx.space),
                        String::from("%number"),
                        value.get_location(),
                    ));
                    None
                } else {
                    Some(ctx.space.resolve_type("%int").unwrap().clone())
                }
            }
        },
        ("floor", _) | ("ceil", _) | ("round", _) => {
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
    ctx: &mut Context,
    lhs: &ValueNode,
    rhs: &ValueNode,
    div: bool,
) -> Option<MarkusType> {
    let lhs_type = lhs.get_type(ctx);
    let rhs_type = rhs.get_type(ctx);

    let number_type = ctx.space.resolve_type("%number").unwrap();

    if !lhs_type.is(ctx.space, number_type) {
        ctx.diagnostics.push(Diagnostic::mismatched_types(
            lhs_type.to_string(ctx.space),
            String::from("%number"),
            lhs.get_location(),
        ));
        return None;
    }

    if !rhs_type.is(ctx.space, number_type) {
        ctx.diagnostics.push(Diagnostic::mismatched_types(
            rhs_type.to_string(ctx.space),
            String::from("%number"),
            rhs.get_location(),
        ));
        return None;
    }

    Some(get_binary_type(ctx, &lhs_type, &rhs_type, div))
}

#[inline(always)]
fn get_binary_type(
    ctx: &mut Context,
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
