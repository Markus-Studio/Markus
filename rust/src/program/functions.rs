use crate::parser::ast::{CallNode, ValueNode, VariableReferenceNode};
use crate::parser::Span;
use crate::program::verify::VerifierContext;
use crate::program::{Diagnostic, MarkusType};

impl CallNode {
    pub fn get_type(&self, ctx: &mut VerifierContext) -> MarkusType {
        get_type(self, ctx)
    }
}

#[inline(always)]
fn get_type(call: &CallNode, ctx: &mut VerifierContext) -> MarkusType {
    MarkusType::new_union(Vec::with_capacity(0))
}
