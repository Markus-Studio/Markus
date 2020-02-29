#![allow(unused)]
use crate::common::Matrix;
use crate::ir::ir::*;
use bimap::BiMap;
use std::collections::{HashMap, HashSet};

pub struct IRBuilder {
    types: Vec<i32>,
}

pub struct TypeSpaceBuilder {
    type_ids: HashMap<String, TypeId>,
    next_id: TypeId,
    objects: HashMap<String, (Vec<(String, String, bool)>, Vec<String>)>,
    current_type_name: Option<String>,
    current_bases: Option<Vec<String>>,
    current_fields: Option<Vec<(String, String, bool)>>,
}

pub struct ValueBuilder {
    stack: Vec<ValueStackItem>,
}

pub struct SelectionBuilder {
    stack: Vec<FilterVector>,
}

pub struct PermissionBuilder {}

pub struct QueryBuilder {}

pub struct ActionBuilder {}

impl IRBuilder {
    pub fn new() -> IRBuilder {
        IRBuilder {
            types: Vec::with_capacity(0),
        }
    }
}

impl TypeSpaceBuilder {
    pub fn new() -> TypeSpaceBuilder {
        let mut space = TypeSpaceBuilder {
            type_ids: HashMap::new(),
            next_id: 0,
            objects: HashMap::new(),
            current_bases: None,
            current_type_name: None,
            current_fields: None,
        };
        space.reserve(String::from("user"));
        space
    }

    fn reserve(&mut self, name: String) {
        let id = self.next_id;
        self.type_ids.insert(name, id);
        self.next_id += 1;
    }

    pub fn begin(&mut self, name: String) {
        self.current_type_name = Some(name);
        self.current_fields = Some(Vec::new());
    }

    pub fn end(&mut self) {
        let type_name = std::mem::replace(&mut self.current_type_name, None).unwrap();
        let fields = std::mem::replace(&mut self.current_fields, None).unwrap();
        let bases = std::mem::replace(&mut self.current_bases, None).unwrap();
        self.objects.insert(type_name, (fields, bases));
    }

    pub fn base(&mut self, name: String) {
        self.current_bases.as_mut().unwrap().push(name);
    }

    pub fn field(&mut self, name: String, field_type: String, nullable: bool) {
        self.current_fields
            .as_mut()
            .unwrap()
            .push((name, field_type, nullable));
    }

    fn stage(&mut self) {
        let mut type_names: Vec<&String> = self.objects.keys().collect();
        type_names.sort_unstable();
        for type_name in &type_names {
            let id = self.next_id;
            self.type_ids.insert((*type_name).clone(), id);
            self.next_id += 1;
        }
    }

    fn get_type(&self, name: &String) -> IrType {
        match name as &str {
            "i32" => IrType::I32,
            _ => {
                let id = *self.type_ids.get(name).unwrap();
                IrType::Object(id)
            }
        }
    }

    pub fn build(mut self) -> TypeSpace {
        self.stage();

        let size = self.next_id;
        let mut base_graph = Matrix::<bool, TypeId>::new(size, size, false);
        let mut type_names = BiMap::new();
        let mut types = HashMap::new();

        for (name, _) in &self.objects {
            let type_id = *self.type_ids.get(name).unwrap();
            let mut object_fields: ObjectTypeData = Vec::new();
            let mut recursive_bases: Vec<&String> = Vec::new();
            let mut cursor = 0;
            let mut seen: HashSet<TypeId> = HashSet::new();
            recursive_bases.push(&name);

            while cursor < recursive_bases.len() {
                let current = recursive_bases[cursor];
                let base_id = *self.type_ids.get(current).unwrap();
                if seen.insert(base_id) == false {
                    continue;
                }

                match self.objects.get(current) {
                    Some((fields, bases)) => {
                        for base in bases {
                            recursive_bases.push(base);
                        }

                        for (name, type_name, optional) in fields {
                            let field_type = self.get_type(type_name);
                            object_fields.push((name.clone(), field_type, *optional))
                        }
                    }
                    _ => {} // An internal type like `user`.
                }

                base_graph.set(type_id, base_id, true);

                cursor += 1;
            }

            type_names.insert(name.clone(), type_id);
        }

        TypeSpace {
            base_graph,
            type_names,
            types,
        }
    }
}

impl ValueBuilder {
    pub fn new() -> ValueBuilder {
        ValueBuilder { stack: Vec::new() }
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

impl SelectionBuilder {
    pub fn new() -> SelectionBuilder {
        SelectionBuilder { stack: Vec::new() }
    }

    pub fn is(&mut self, type_id: TypeId) {
        self.stack
            .push(FilterVector::from_filter(AtomicFilter::Is(type_id), false));
    }

    pub fn eq(&mut self, lhs: Value, rhs: Value) {
        self.stack
            .push(FilterVector::from_filter(AtomicFilter::Eq(lhs, rhs), false));
    }

    pub fn neq(&mut self, lhs: Value, rhs: Value) {
        self.stack
            .push(FilterVector::from_filter(AtomicFilter::Eq(lhs, rhs), true));
    }

    pub fn gt(&mut self, lhs: Value, rhs: Value) {
        self.stack
            .push(FilterVector::from_filter(AtomicFilter::Gt(lhs, rhs), false));
    }

    pub fn gte(&mut self, lhs: Value, rhs: Value) {
        self.stack
            .push(FilterVector::from_filter(AtomicFilter::Lt(lhs, rhs), true));
    }

    pub fn lt(&mut self, lhs: Value, rhs: Value) {
        self.stack
            .push(FilterVector::from_filter(AtomicFilter::Lt(lhs, rhs), false));
    }

    pub fn lte(&mut self, lhs: Value, rhs: Value) {
        self.stack
            .push(FilterVector::from_filter(AtomicFilter::Gt(lhs, rhs), true));
    }

    #[cfg(test)]
    pub fn test_variable(&mut self, id: usize) {
        self.stack.push(FilterVector::from_filter(
            AtomicFilter::TestVariable(id),
            false,
        ));
    }

    pub fn and(&mut self) {
        let rhs = self.stack.pop().unwrap();
        let lhs = self.stack.pop().unwrap();
        self.stack.push(lhs * rhs);
    }

    pub fn or(&mut self) {
        let rhs = self.stack.pop().unwrap();
        let lhs = self.stack.pop().unwrap();
        self.stack.push(lhs + rhs);
    }

    pub fn neg(&mut self) {
        let value = self.stack.pop().unwrap();
        self.stack.push(-value);
    }

    pub fn build(mut self) -> Selection {
        assert_eq!(self.stack.len(), 1);
        self.stack.pop().unwrap()
    }
}

impl PermissionBuilder {
    pub fn new() -> PermissionBuilder {
        PermissionBuilder {}
    }
}

impl QueryBuilder {
    pub fn new() -> QueryBuilder {
        QueryBuilder {}
    }
}

impl ActionBuilder {
    pub fn new() -> ActionBuilder {
        ActionBuilder {}
    }
}
