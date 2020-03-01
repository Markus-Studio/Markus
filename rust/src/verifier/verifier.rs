use crate::parser::ast::{ActionDeclarationNode, QueryDeclarationNode};
use crate::parser::ast::{ActionStatement, CreateStatementNode, ValidateStatementNode};
use crate::parser::ast::{BindingValueNode, DeleteStatementNode, UpdateStatementNode};
use crate::parser::ast::{GuardNode, ParameterNode, PermissionDeclarationNode};
use crate::parser::Span;
use crate::program::{Diagnostic, MarkusType, TypeSpace};
use std::collections::HashMap;

pub struct Context<'a> {
    pub space: &'a mut TypeSpace,
    pub diagnostics: &'a mut Vec<Diagnostic>,
    pub symbol_table: HashMap<String, MarkusType>,
    pub only_filters: bool,
    branches: Vec<Vec<MarkusType>>,
    current: Vec<MarkusType>,
}

impl<'a> Context<'a> {
    #[inline(always)]
    pub fn new(
        diagnostics: &'a mut Vec<Diagnostic>,
        space: &'a mut TypeSpace,
        input_type: MarkusType,
        only_filters: bool,
        parameters: &Vec<ParameterNode>,
    ) -> Context<'a> {
        let mut symbol_table = HashMap::new();
        let null_id = space.resolve_type("null").unwrap().get_id();
        for parameter in parameters {
            if None == parameter.name || None == parameter.type_name {
                continue;
            }

            match (parameter.name.as_ref(), parameter.type_name.as_ref()) {
                (Some(parameter_name), None) => {
                    if symbol_table.contains_key(&parameter_name.value) {
                        diagnostics.push(Diagnostic::name_already_in_use(&parameter_name));
                    }
                }
                (None, _) => {}
                (Some(parameter_name), Some(type_name)) => {
                    let name = String::from(&parameter_name.value);

                    if symbol_table.contains_key(&name) {
                        diagnostics.push(Diagnostic::name_already_in_use(&parameter_name));
                    }

                    if let Some(parameter_type) = space.resolve_type(&type_name.value) {
                        if parameter.optional {
                            let type_id = parameter_type.get_id();
                            symbol_table
                                .insert(name, MarkusType::new_union(vec![null_id, type_id]));
                        } else {
                            symbol_table.insert(name, parameter_type.clone());
                        }
                    } else {
                        diagnostics.push(Diagnostic::unresolved_name(&type_name));
                    }
                }
            }
        }

        Context {
            space,
            diagnostics,
            only_filters,
            branches: Vec::new(),
            current: vec![input_type],
            symbol_table: HashMap::new(),
        }
    }

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

    /// To be used in groupBy.
    #[inline]
    pub fn branch_pop(&mut self) -> MarkusType {
        let types = self.branches.pop().unwrap();
        MarkusType::create_union_from(types)
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
}

impl PermissionDeclarationNode {
    pub fn verify<'a>(
        &self,
        diagnostics: &mut Vec<Diagnostic>,
        space: &'a mut TypeSpace,
    ) -> MarkusType {
        let mut ctx = Context::new(
            diagnostics,
            space,
            space.get_permission_input_type(),
            true,
            &self.parameters,
        );
        self.query.get_type(&mut ctx)
    }
}

impl QueryDeclarationNode {
    pub fn verify<'a>(
        &self,
        diagnostics: &'a mut Vec<Diagnostic>,
        space: &'a mut TypeSpace,
        permissions: &'a HashMap<String, (Vec<Option<MarkusType>>, MarkusType)>,
    ) -> MarkusType {
        let default_user_type = space.get_permission_input_type();
        let mut ctx = Context::new(
            diagnostics,
            space,
            space.get_query_input_type(),
            false,
            &self.parameters,
        );
        ctx.symbol_table.insert(
            String::from("%user"),
            create_user_type(
                ctx.diagnostics,
                default_user_type,
                permissions,
                &self.guards,
            ),
        );
        self.query.get_type(&mut ctx)
    }
}

impl ActionDeclarationNode {
    pub fn verify<'a>(
        &self,
        diagnostics: &mut Vec<Diagnostic>,
        space: &'a mut TypeSpace,
        permissions: &'a HashMap<String, (Vec<Option<MarkusType>>, MarkusType)>,
    ) {
        let default_user_type = space.get_permission_input_type();
        let mut ctx = Context::new(
            diagnostics,
            space,
            space.get_query_input_type(),
            false,
            &self.parameters,
        );
        ctx.symbol_table.insert(
            String::from("%user"),
            create_user_type(
                ctx.diagnostics,
                default_user_type,
                permissions,
                &self.guards,
            ),
        );

        for statement in &self.statements {
            ctx.branch_in();
            ctx.path_enter();
            match statement {
                ActionStatement::Validate(stmt) => {
                    stmt.verify(&mut ctx);
                }
                ActionStatement::Delete(stmt) => {
                    stmt.verify(&mut ctx);
                }
                ActionStatement::Update(stmt) => {
                    stmt.verify(&mut ctx);
                }
                ActionStatement::Create(stmt) => {
                    stmt.verify(&mut ctx);
                }
            }
            ctx.path_exit();
            ctx.branch_pop();
        }
    }
}

impl ValidateStatementNode {
    pub fn verify(&self, ctx: &mut Context) {
        if let Some(call) = &self.value {
            // TODO(qti3e) This function must return a boolean.
            call.get_type(ctx);
        }
    }
}

impl DeleteStatementNode {
    pub fn verify(&self, ctx: &mut Context) {
        if let Some(base) = &self.base {
            let base_type = base.get_type(ctx);
            if base_type.is_nil() {
                ctx.diagnostics.push(Diagnostic::nil_base(base));
                return;
            }
        }
    }
}

impl UpdateStatementNode {
    pub fn verify(&self, ctx: &mut Context) {
        if let (Some(base), Some(updates)) = (&self.base, &self.updates) {
            let base_type = base.get_type(ctx);

            if base_type.is_nil() {
                ctx.diagnostics.push(Diagnostic::nil_base(base));
                return;
            }

            let mut modified: Vec<(Vec<&str>, Span)> = Vec::with_capacity(updates.bindings.len());
            let base_type_str = base_type.to_string(ctx.space);

            for binding in &updates.bindings {
                let mut uri: Vec<&str> = Vec::with_capacity(binding.uri.len());

                for part in &binding.uri {
                    uri.push(&part.value);
                }

                let field_type_option = base_type.query(ctx.space, &uri);

                if field_type_option.is_none() || uri.len() == 0 {
                    ctx.diagnostics.push(Diagnostic::field_not_found(
                        base_type_str.to_string(),
                        uri,
                        binding.location,
                    ));
                    continue;
                }

                if let Some(value) = &binding.value {
                    match value {
                        BindingValueNode::Create(statement) => {
                            statement.verify(ctx);
                        }
                        _ => {}
                    }
                    let mut field_type = field_type_option.unwrap();
                    if base_type.is_nullable(ctx.space, &uri) {
                        field_type = field_type + ctx.space.resolve_type("null").unwrap();
                    }
                    let value_type = value.get_type(ctx);
                    if !value_type.is(ctx.space, &field_type) {
                        ctx.diagnostics.push(Diagnostic::binding_type_error(
                            field_type.to_string(ctx.space),
                            value_type.to_string(ctx.space),
                            binding.location,
                        ));
                    }
                }

                modified.push((uri, binding.uri[0].location));
            }

            modified.sort_by(|a, b| a.0.len().partial_cmp(&b.0.len()).unwrap());

            for i in 0..modified.len() {
                let current = &modified[i].0;
                let current_len = current.len();
                for j in i + 1..modified.len() {
                    let second = &modified[j].0;
                    if second.len() == current_len {
                        continue;
                    }

                    let mut same = true;
                    for t in 0..current_len {
                        if current[t] != second[t] {
                            same = false;
                            break;
                        }
                    }

                    if same {
                        ctx.diagnostics
                            .push(Diagnostic::update_already_modified_field(modified[j].1));
                    }
                }
            }
        }
    }
}

impl CreateStatementNode {
    pub fn verify(&self, ctx: &mut Context) {}
}

fn create_user_type(
    diagnostics: &mut Vec<Diagnostic>,
    default: MarkusType,
    permission_types: &HashMap<String, (Vec<Option<MarkusType>>, MarkusType)>,
    permissions: &Vec<GuardNode>,
) -> MarkusType {
    if permission_types.len() == 0 {
        default
    } else {
        let mut result = MarkusType::new_union(Vec::with_capacity(0));

        for permission in permissions {
            // TODO(qti3e) Report binding errors.
            if let Some(call) = &permission.call {
                if let Some(callee_name) = &call.callee_name {
                    if let Some((_, result_type)) = permission_types.get(&callee_name.value) {
                        result = result + result_type;
                    } else {
                        diagnostics.push(Diagnostic::unresolved_name(callee_name));
                    }
                }
            }
        }

        result
    }
}
