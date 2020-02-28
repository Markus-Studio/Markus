#![allow(unused)]
use crate::ir::ir::*;
use crate::ir::typespace::IrType;

pub struct IRBuilder {
    types: Vec<i32>,
}

pub struct TypeBuilder<'a> {
    builder: &'a mut IRBuilder,
}

pub struct ValueBuilder<'a> {
    builder: &'a mut IRBuilder,
    stack: Vec<ValueStackItem>,
}

pub struct SelectionBuilder<'a> {
    builder: &'a mut IRBuilder,
}

pub struct PermissionBuilder<'a> {
    builder: &'a mut IRBuilder,
}

pub struct QueryBuilder<'a> {
    builder: &'a mut IRBuilder,
}

pub struct ActionBuilder<'a> {
    builder: &'a mut IRBuilder,
}

impl IRBuilder {
    pub fn new() -> IRBuilder {
        IRBuilder {
            types: Vec::with_capacity(0),
        }
    }
}

impl<'a> TypeBuilder<'a> {
    pub fn new(builder: &'a mut IRBuilder) -> TypeBuilder<'a> {
        TypeBuilder { builder }
    }

    pub fn build(&self) {}
}

impl<'a> ValueBuilder<'a> {
    pub fn new(builder: &'a mut IRBuilder) -> ValueBuilder<'a> {
        ValueBuilder {
            builder,
            stack: Vec::new(),
        }
    }

    pub fn push_i32(&mut self, value: i32) {
        self.stack
            .push(ValueStackItem::Literal(ValueLiteral::I32(value)));
    }

    pub fn push_i64(&mut self, value: i64) {
        self.stack
            .push(ValueStackItem::Literal(ValueLiteral::I64(value)));
    }

    pub fn push_u32(&mut self, value: u32) {
        self.stack
            .push(ValueStackItem::Literal(ValueLiteral::U32(value)));
    }

    pub fn push_u64(&mut self, value: u64) {
        self.stack
            .push(ValueStackItem::Literal(ValueLiteral::U64(value)));
    }

    pub fn push_f32(&mut self, value: f32) {
        self.stack
            .push(ValueStackItem::Literal(ValueLiteral::F32(value)));
    }

    pub fn push_f64(&mut self, value: f64) {
        self.stack
            .push(ValueStackItem::Literal(ValueLiteral::F64(value)));
    }

    pub fn push_null(&mut self) {
        self.stack.push(ValueStackItem::Literal(ValueLiteral::Null));
    }

    pub fn push_true(&mut self) {
        self.stack.push(ValueStackItem::Literal(ValueLiteral::True));
    }

    pub fn push_false(&mut self) {
        self.stack
            .push(ValueStackItem::Literal(ValueLiteral::False));
    }

    pub fn push_string(&mut self, value: String) {
        self.stack
            .push(ValueStackItem::Literal(ValueLiteral::Str(value)));
    }

    pub fn push_current(&mut self, current_type: Vec<IrType>) {
        self.stack.push(ValueStackItem::Variable(
            ValueVariableBase::Current,
            current_type,
            Vec::new(),
        ));
    }

    pub fn push_user(&mut self, user_type: Vec<IrType>) {
        self.stack.push(ValueStackItem::Variable(
            ValueVariableBase::User,
            user_type,
            Vec::new(),
        ));
    }

    pub fn push_variable(&mut self, name: String, variable_type: Vec<IrType>) {
        self.stack.push(ValueStackItem::Variable(
            ValueVariableBase::Named(name),
            variable_type,
            Vec::new(),
        ));
    }

    pub fn get_field(&mut self, name: String, field_type: Vec<IrType>) {
        let mut item = self.stack.pop().unwrap();
        match item {
            ValueStackItem::Variable(base, base_type, mut fields) => {
                fields.push((name, field_type));
                self.stack
                    .push(ValueStackItem::Variable(base, base_type, fields));
            }
            _ => panic!("Get field must only be called after a base."),
        }
    }

    fn is_literal2(&self) -> bool {
        match (
            &self.stack[self.stack.len() - 1],
            &self.stack[self.stack.len() - 2],
        ) {
            (ValueStackItem::Literal(_), ValueStackItem::Literal(_)) => true,
            _ => false,
        }
    }

    pub fn add(&mut self) {
        if self.is_literal2() {
            let rhs = self.stack.pop().unwrap().as_literal();
            let lhs = self.stack.pop().unwrap().as_literal();
            let result = lhs + &rhs;
            self.stack.push(ValueStackItem::Literal(result));
        } else {
            self.stack
                .push(ValueStackItem::Function(ValueFunction::Add));
        }
    }

    pub fn sub(&mut self) {
        if self.is_literal2() {
            let rhs = self.stack.pop().unwrap().as_literal();
            let lhs = self.stack.pop().unwrap().as_literal();
            let result = lhs - &rhs;
            self.stack.push(ValueStackItem::Literal(result));
        } else {
            self.stack
                .push(ValueStackItem::Function(ValueFunction::Sub));
        }
    }

    pub fn mul(&mut self) {
        if self.is_literal2() {
            let rhs = self.stack.pop().unwrap().as_literal();
            let lhs = self.stack.pop().unwrap().as_literal();
            let result = lhs * &rhs;
            self.stack.push(ValueStackItem::Literal(result));
        } else {
            self.stack
                .push(ValueStackItem::Function(ValueFunction::Mul));
        }
    }

    pub fn div(&mut self) {
        if self.is_literal2() {
            let rhs = self.stack.pop().unwrap().as_literal();
            let lhs = self.stack.pop().unwrap().as_literal();
            let result = lhs / &rhs;
            self.stack.push(ValueStackItem::Literal(result));
        } else {
            self.stack
                .push(ValueStackItem::Function(ValueFunction::Div));
        }
    }

    pub fn build(self) -> Value {
        self.stack
    }
}

impl<'a> SelectionBuilder<'a> {
    pub fn new(builder: &'a mut IRBuilder) -> SelectionBuilder<'a> {
        SelectionBuilder { builder }
    }
}

impl<'a> PermissionBuilder<'a> {
    pub fn new(builder: &'a mut IRBuilder) -> PermissionBuilder<'a> {
        PermissionBuilder { builder }
    }
}

impl<'a> QueryBuilder<'a> {
    pub fn new(builder: &'a mut IRBuilder) -> QueryBuilder<'a> {
        QueryBuilder { builder }
    }
}

impl<'a> ActionBuilder<'a> {
    pub fn new(builder: &'a mut IRBuilder) -> ActionBuilder<'a> {
        ActionBuilder { builder }
    }
}
