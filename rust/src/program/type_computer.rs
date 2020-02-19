use crate::parser::ast::{IntLiteralNode, QueryNode, ValueNode, VariableReferenceNode};
use crate::program::verify::VerifierContext;
use crate::program::{Diagnostic, MarkusType};

impl VariableReferenceNode {
    pub fn get_type(&self, ctx: &mut VerifierContext) -> MarkusType {
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

impl ValueNode {
    /// Computes and returns type of this value.
    pub fn get_type(&self, ctx: &mut VerifierContext) -> MarkusType {
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
                let base_type = access.base.get_type(ctx);
                match base_type.query(ctx.space, &uri) {
                    Some(data_type) => data_type,
                    _ => {
                        let type_str = base_type.to_string(ctx.space);
                        ctx.diagnostics.push(Diagnostic::field_not_found(
                            type_str,
                            uri,
                            access.location,
                        ));
                        MarkusType::new_union(Vec::with_capacity(0))
                    }
                }
            }
            ValueNode::Call(call) => call.get_type(ctx),
            _ => panic!("Not implemented."),
        }
    }
}

impl QueryNode {
    pub fn get_type(&self, ctx: &mut VerifierContext) -> MarkusType {
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
