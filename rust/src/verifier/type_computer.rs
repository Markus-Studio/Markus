use crate::parser::ast::{AccessNode, ActionBase, VariableReferenceNode};
use crate::parser::ast::{BindingValueNode, IntLiteralNode, QueryNode, ValueNode};
use crate::program::{Diagnostic, MarkusType};
use crate::verifier::Context;

impl VariableReferenceNode {
    pub fn get_type(&self, ctx: &mut Context) -> MarkusType {
        match self {
            VariableReferenceNode::Current => {
                let current = ctx.get_current();
                current.with_dimension(current.dimension - 1)
            }
            VariableReferenceNode::Internal(id) | VariableReferenceNode::Variable(id) => {
                if let Some(variable_type) = ctx.symbol_table.get(&id.value) {
                    variable_type.clone()
                } else {
                    ctx.diagnostics.push(Diagnostic::unresolved_name(&id));
                    MarkusType::new_union(Vec::with_capacity(0))
                }
            }
        }
    }
}

impl AccessNode {
    pub fn get_type(&self, ctx: &mut Context) -> MarkusType {
        let uri: Vec<&str> = self.parts.iter().map(|p| &*p.value).collect();
        let base_type = self.base.get_type(ctx);
        match base_type.query(ctx.space, &uri) {
            Some(data_type) => data_type,
            _ => {
                let type_str = base_type.to_string(ctx.space);
                ctx.diagnostics
                    .push(Diagnostic::field_not_found(type_str, uri, self.location));
                MarkusType::new_union(Vec::with_capacity(0))
            }
        }
    }
}

impl ValueNode {
    /// Computes and returns type of this value.
    pub fn get_type(&self, ctx: &mut Context) -> MarkusType {
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
            ValueNode::Access(access) => access.get_type(ctx),
            ValueNode::Call(call) => call.get_type(ctx),
            ValueNode::Type(_) => panic!("get_type() does not work on a type reference."),
            ValueNode::Query(_) => unimplemented!(),
        }
    }
}

impl BindingValueNode {
    /// Computes and returns type of this value.
    pub fn get_type(&self, ctx: &mut Context) -> MarkusType {
        match self {
            BindingValueNode::Int(IntLiteralNode { neg, .. }) => {
                if *neg {
                    ctx.space.resolve_type("%neg-int").unwrap().clone()
                } else {
                    ctx.space.resolve_type("%int").unwrap().clone()
                }
            }
            BindingValueNode::Float(_) => ctx.space.resolve_type("%float").unwrap().clone(),
            BindingValueNode::Boolean(_) => ctx.space.resolve_type("bool").unwrap().clone(),
            BindingValueNode::Null(_) => ctx.space.resolve_type("null").unwrap().clone(),
            BindingValueNode::String(_) => ctx.space.resolve_type("string").unwrap().clone(),
            BindingValueNode::Access(access) => access.get_type(ctx),
            BindingValueNode::Call(call) => call.get_type(ctx),
            BindingValueNode::Create(create) => {
                if let Some(name) = &create.base {
                    match ctx.space.resolve_type(&name.value) {
                        Some(field_type) => field_type.to_owned(),
                        None => MarkusType::new_nil(),
                    }
                } else {
                    MarkusType::new_nil()
                }
            }
        }
    }
}

impl QueryNode {
    pub fn get_type(&self, ctx: &mut Context) -> MarkusType {
        for pipeline in &self.pipelines {
            pipeline.apply_pipeline_changes(ctx);
            if ctx.get_current().is_nil() {
                ctx.diagnostics.push(Diagnostic::reached_nil(pipeline));
                break;
            }
        }
        ctx.get_current().clone()
    }
}

impl ActionBase {
    pub fn get_type(&self, ctx: &mut Context) -> MarkusType {
        match self {
            ActionBase::Access(access) => access.get_type(ctx),
            ActionBase::Query(query) => query.get_type(ctx),
        }
    }
}
