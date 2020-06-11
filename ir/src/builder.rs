#![allow(unused)]
//! The builder module provides an API to build valid Markus IRs.
//!
//! In order to build a IR-Program one must first create the type space, and to do that they
//! can use [`TypeSpaceBuilder`] after creating the TypeSpace we construct an [`IRBuilder`]
//! providing the generated TypeSpace, the next step is adding Queries and then Actions using
//! [`QueryBuilder`] and [`ActionBuilder`] accordingly.
//!
//! [`TypeSpaceBuilder`]: struct.TypeSpaceBuilder.html
//! [`IRBuilder`]: struct.IRBuilder.html
//! [`QueryBuilder`]: struct.QueryBuilder.html
//! [`ActionBuilder`]: struct.ActionBuilder.html

use crate::ir::*;
use common::bimap::BiMap;
use common::matrix::Matrix;
use std::collections::{HashMap, HashSet};

/// The builder used to build an IR-Programs.
pub struct IRBuilder {
    /// The type space used in this program.
    pub typespace: TypeSpace,
}

/// The builder used to build a TypeSpace.
///
/// Every program has one and only one TypeSpace, that contains all of the information
/// for each user-defined-object-type including the BaseGraph and fields and their types.
///
/// This Builder can be used to generate the TypeSpace in a non-recursive manner.
///
/// # Example
/// ```
/// // type A { x: u32; y?: u32; } type B: A {}
/// let mut builder = TypeSpaceBuilder::new();
/// builder.begin("A");
/// builder.field("x", "u32", false);
/// builder.field("y", "u32", true);
/// builder.end();
/// builder.begin("B");
/// builder.base("A");
/// builder.end();
/// let typespace = builder.build();
/// ```
pub struct TypeSpaceBuilder {
    /// Maps every type name to its id.
    type_ids: HashMap<String, TypeId>,
    /// TypeId counter.
    next_id: TypeId,
    /// Maps every type name to its fields and bases.
    /// Field: (FieldName, TypeName, Optional)
    objects: HashMap<String, (Vec<(String, String, bool)>, Vec<String>)>,
    /// Name of the current type (last call to begin()).
    current_type_name: Option<String>,
    /// Stores bases for the current type.
    current_bases: Option<Vec<String>>,
    /// Stores fields for the current type.
    current_fields: Option<Vec<(String, String, bool)>>,
}

/// Helper to build IR-Values.
///
/// The `ValueBuilder` provides an stack-machine like API to build IR-Values.
///
/// # Example
/// ```
/// // 5 + 3 * 2
/// let builder = ValueBuilder::new();
/// builder.push_i32(5);
/// builder.push_i32(3);
/// builder.push_i32(2);
/// builder.mul();
/// builder.add();
/// let value = builder.build();
/// ```
pub struct ValueBuilder {
    /// The items in the stack.
    stack: Vec<ValueStackItem>,
}

/// Helper to build Selections.
///
/// A selection is a function that returns a boolean and a value is filtered based
/// on the returned value, in Markus there are some Atomic filters and as the name
/// suggests those are the filters that can not be made by combining two or more
/// functions, such as `is`, `eq`, `lt` and `gt`, but not `lte` as it can be created
/// using `not(gt)`.
///
/// In Markus-IR we try to store selections in a normalized format which is a set of
/// Conjunctions (and) that we perform the OR operator between each of them , and
/// every conjunction is just made up Atomic filter + a flag indicating if that atomic
/// filter is negated or not.
///
/// So `A & B` can be written as `[AB]` and `A | (B & C)` can be written as `[A, BC]`.
///
/// Theoretically speaking this is not an efficient way and somewhat is considered to
/// be expensive and should be avoided, but most of the Markus queries will not be that
/// complex to cause problems and it works very well for things such as redundancy-
/// elimination, index selection, action-on-query impact computation, etc.
///
/// The current implementation can be viewed as a partial SAT-solver as it evaluates
/// expressions such as `A & !A` to `False` and `A | !A` to `True`.
///
/// # Example
/// ```
/// // { is(A), or(eq(.x, 5), not(gt(.y, 1))) }
/// let builder = SelectionBuilder::new();
/// builder.is(...);
/// builder.eq(...);
/// builder.gt(...);
/// builder.not();
/// builder.or();
/// builder.and();
/// builder.build()
/// ```
pub struct SelectionBuilder {
    stack: Vec<FilterVector>,
}

pub struct QueryBuilder<'a> {
    builder: &'a IRBuilder,
    parameters: Vec<(String, IrType, bool)>,
    current_selection: SelectionBuilder,
}

pub struct ActionBuilder {}

impl IRBuilder {
    /// Constructs a new IRBuilder.
    pub fn new(typespace: TypeSpace) -> IRBuilder {
        IRBuilder { typespace }
    }

    /// Returns the TypeId for the given object type.
    pub fn resolve_type_id(&self, name: &String) -> TypeId {
        *self
            .typespace
            .type_names
            .get_by_left(name)
            .expect("Failed to resolve a type.")
    }

    /// Returns the IrType for the given name.
    pub fn get_type(&self, name: &String) -> IrType {
        match name as &str {
            "null" => IrType::Null,
            "i32" => IrType::I32,
            "i64" => IrType::I64,
            "u32" => IrType::U32,
            "u64" => IrType::U64,
            "f32" => IrType::F32,
            "f64" => IrType::F64,
            "time" => IrType::Time,
            "string" => IrType::Str,
            "bool" => IrType::Bool,
            _ => {
                let id = self.resolve_type_id(name);
                IrType::Object(id)
            }
        }
    }
}

impl TypeSpaceBuilder {
    /// Constructs a new empty TypeSpaceBuilder.
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

    /// Reserves a type id for the given name, used to reserve id for internal types such as
    /// `user`.
    fn reserve(&mut self, name: String) {
        let id = self.next_id;
        self.type_ids.insert(name, id);
        self.next_id += 1;
    }

    /// Start building a new type in the current typespace with the given name, one must
    /// call `end()` at the end of implementation.
    /// # Panics
    /// Two consecutive calls to `begin()` without an `end()` call in between causes
    /// a panic.
    pub fn begin(&mut self, name: String) {
        assert!(self.current_type_name.is_none());
        self.current_type_name = Some(name);
        self.current_fields = Some(Vec::new());
        self.current_bases = Some(Vec::new());
    }

    /// Ends implementation of the current type, must be called at the end of each call
    /// to `begin()`.
    /// # Panics
    /// If there isn't a open implementation (no call to `begin()` before this call.)
    pub fn end(&mut self) {
        let type_name = std::mem::replace(&mut self.current_type_name, None).unwrap();
        let fields = std::mem::replace(&mut self.current_fields, None).unwrap();
        let bases = std::mem::replace(&mut self.current_bases, None).unwrap();
        self.objects.insert(type_name, (fields, bases));
    }

    /// Adds a base with the given name to the current type.
    /// # Panics
    /// If there is no open implementation.
    pub fn base(&mut self, name: String) {
        self.current_bases.as_mut().unwrap().push(name);
    }

    /// Adds a field with the given information to this type.
    /// # Panics
    /// If there is no open implementation.
    pub fn field(&mut self, name: String, field_type: String, nullable: bool) {
        self.current_fields
            .as_mut()
            .unwrap()
            .push((name, field_type, nullable));
    }

    /// Assigns an ID to all of the types that do not have an ID yet.
    fn stage(&mut self) {
        let mut type_names: Vec<&String> = self.objects.keys().collect();
        type_names.sort_unstable();
        for type_name in &type_names {
            let id = self.next_id;
            self.type_ids.insert((*type_name).clone(), id);
            self.next_id += 1;
        }
    }

    /// Returns an `IrType` for the type with the given name.
    fn get_type(&self, name: &String) -> IrType {
        match name as &str {
            "null" => IrType::Null,
            "i32" => IrType::I32,
            "i64" => IrType::I64,
            "u32" => IrType::U32,
            "u64" => IrType::U64,
            "f32" => IrType::F32,
            "f64" => IrType::F64,
            "time" => IrType::Time,
            "string" => IrType::Str,
            "bool" => IrType::Bool,
            _ => {
                let id = *self.type_ids.get(name).unwrap();
                IrType::Object(id)
            }
        }
    }

    /// Build the final `TypeSpace` and returns it.
    /// # Panics
    /// If there is an open implementation (a call to `begin()` without `end()`) or
    /// when a field type can not be resolved.
    pub fn build(mut self) -> TypeSpace {
        assert!(self.current_type_name.is_none());
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
    /// Constructs a new ValueBuilder.
    pub fn new() -> ValueBuilder {
        ValueBuilder { stack: Vec::new() }
    }

    /// Pushes an `i32` number to the stack.
    pub fn push_i32(&mut self, value: i32) {
        self.stack
            .push(ValueStackItem::Literal(ValueLiteral::I32(value)));
    }

    /// Pushes an `i64` number to the stack.
    pub fn push_i64(&mut self, value: i64) {
        self.stack
            .push(ValueStackItem::Literal(ValueLiteral::I64(value)));
    }

    /// Pushes a `u32` number to the stack.
    pub fn push_u32(&mut self, value: u32) {
        self.stack
            .push(ValueStackItem::Literal(ValueLiteral::U32(value)));
    }

    /// Pushes a `u64` number to the stack.
    pub fn push_u64(&mut self, value: u64) {
        self.stack
            .push(ValueStackItem::Literal(ValueLiteral::U64(value)));
    }

    /// Pushes a `f32` number to the stack.
    pub fn push_f32(&mut self, value: f32) {
        self.stack
            .push(ValueStackItem::Literal(ValueLiteral::F32(value)));
    }

    /// Pushes a `f64` number to the stack.
    pub fn push_f64(&mut self, value: f64) {
        self.stack
            .push(ValueStackItem::Literal(ValueLiteral::F64(value)));
    }

    /// Pushes the `null` in to the stack.
    pub fn push_null(&mut self) {
        self.stack.push(ValueStackItem::Literal(ValueLiteral::Null));
    }

    /// Pushes `true` in to the stack.
    pub fn push_true(&mut self) {
        self.stack.push(ValueStackItem::Literal(ValueLiteral::True));
    }

    /// Pushes `false` in to the stack.
    pub fn push_false(&mut self) {
        self.stack
            .push(ValueStackItem::Literal(ValueLiteral::False));
    }

    /// Pushes the given string in to the stack.
    pub fn push_string(&mut self, value: String) {
        self.stack
            .push(ValueStackItem::Literal(ValueLiteral::Str(value)));
    }

    /// Pushes the `%current` value to the stack.
    pub fn push_current(&mut self, current_type: Vec<IrType>) {
        self.stack.push(ValueStackItem::Variable(
            ValueVariableBase::Current,
            current_type,
            Vec::new(),
        ));
    }

    /// Pushes the `%user` value to the stack.
    pub fn push_user(&mut self, user_type: Vec<IrType>) {
        self.stack.push(ValueStackItem::Variable(
            ValueVariableBase::User,
            user_type,
            Vec::new(),
        ));
    }

    /// Pushes the given variable to the stack.
    pub fn push_variable(&mut self, name: String, variable_type: Vec<IrType>) {
        self.stack.push(ValueStackItem::Variable(
            ValueVariableBase::Named(name),
            variable_type,
            Vec::new(),
        ));
    }

    /// Gets the given field from the last value in the stack.
    /// # Panics
    /// If the last value in the stack is not a variable.
    /// # Example
    /// ```
    /// // .point.y + 5
    /// let builder = ValueBuilder::new();
    /// builder.push_current(current_type);
    /// builder.get_field("point", point_type);
    /// builder.get_field("y", y_type);
    /// builder.push_i32(5);
    /// builder.add();
    /// builder.build()
    /// ```
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

    /// Returns true if there are two literals in the stack.
    fn has_two_literals(&self) -> bool {
        let len = self.stack.len();
        if len < 2 {
            return false;
        }

        match (
            &self.stack[self.stack.len() - 1],
            &self.stack[self.stack.len() - 2],
        ) {
            (ValueStackItem::Literal(_), ValueStackItem::Literal(_)) => true,
            _ => false,
        }
    }

    /// Pushes the `add` function to the stack, if there are two literals in the
    /// stack pops them and pushes the result of performing the operation.
    pub fn add(&mut self) {
        if self.has_two_literals() {
            let rhs = self.stack.pop().unwrap().as_literal();
            let lhs = self.stack.pop().unwrap().as_literal();
            let result = lhs + &rhs;
            self.stack.push(ValueStackItem::Literal(result));
        } else {
            self.stack
                .push(ValueStackItem::Function(ValueFunction::Add));
        }
    }

    /// Pushes the `sub` function to the stack, if there are two literals in the
    /// stack pops them and pushes the result of performing the operation.
    pub fn sub(&mut self) {
        if self.has_two_literals() {
            let rhs = self.stack.pop().unwrap().as_literal();
            let lhs = self.stack.pop().unwrap().as_literal();
            let result = lhs - &rhs;
            self.stack.push(ValueStackItem::Literal(result));
        } else {
            self.stack
                .push(ValueStackItem::Function(ValueFunction::Sub));
        }
    }

    /// Pushes the `mul` function to the stack, if there are two literals in the
    /// stack pops them and pushes the result of performing the operation.
    pub fn mul(&mut self) {
        if self.has_two_literals() {
            let rhs = self.stack.pop().unwrap().as_literal();
            let lhs = self.stack.pop().unwrap().as_literal();
            let result = lhs * &rhs;
            self.stack.push(ValueStackItem::Literal(result));
        } else {
            self.stack
                .push(ValueStackItem::Function(ValueFunction::Mul));
        }
    }

    /// Pushes the `div` function to the stack, if there are two literals in the
    /// stack pops them and pushes the result of performing the operation.
    pub fn div(&mut self) {
        if self.has_two_literals() {
            let rhs = self.stack.pop().unwrap().as_literal();
            let lhs = self.stack.pop().unwrap().as_literal();
            let result = lhs / &rhs;
            self.stack.push(ValueStackItem::Literal(result));
        } else {
            self.stack
                .push(ValueStackItem::Function(ValueFunction::Div));
        }
    }

    /// Builds the value and returns it.
    pub fn build(self) -> Value {
        self.stack
    }
}

impl SelectionBuilder {
    /// Constructs a new SelectionBuilder.
    pub fn new() -> SelectionBuilder {
        SelectionBuilder { stack: Vec::new() }
    }

    /// Adds the `is` filter.
    pub fn is(&mut self, type_id: TypeId) {
        self.stack
            .push(FilterVector::from_filter(AtomicFilter::Is(type_id), false));
    }

    /// Adds an `eq` filter with the given values.
    pub fn eq(&mut self, lhs: Value, rhs: Value) {
        self.stack
            .push(FilterVector::from_filter(AtomicFilter::Eq(lhs, rhs), false));
    }

    /// Adds a `not(eq)` filter with the given values.
    pub fn neq(&mut self, lhs: Value, rhs: Value) {
        self.stack
            .push(FilterVector::from_filter(AtomicFilter::Eq(lhs, rhs), true));
    }

    /// Adds a `gt` filter with the given values.
    pub fn gt(&mut self, lhs: Value, rhs: Value) {
        self.stack
            .push(FilterVector::from_filter(AtomicFilter::Gt(lhs, rhs), false));
    }

    /// Adds a `not(lt)` filter with the given values.
    pub fn gte(&mut self, lhs: Value, rhs: Value) {
        self.stack
            .push(FilterVector::from_filter(AtomicFilter::Lt(lhs, rhs), true));
    }

    /// Adds a `lt` filter with the given values.
    pub fn lt(&mut self, lhs: Value, rhs: Value) {
        self.stack
            .push(FilterVector::from_filter(AtomicFilter::Lt(lhs, rhs), false));
    }

    /// Adds a `not(gt)` filter with the given values.
    pub fn lte(&mut self, lhs: Value, rhs: Value) {
        self.stack
            .push(FilterVector::from_filter(AtomicFilter::Gt(lhs, rhs), true));
    }

    /// The test variable is an Atomic constant filter used for testing
    /// purpose.
    pub fn test_variable(&mut self, id: usize) {
        self.stack.push(FilterVector::from_filter(
            AtomicFilter::TestVariable(id),
            false,
        ));
    }

    /// Runs the `and` operation.
    pub fn and(&mut self) {
        let rhs = self.stack.pop().unwrap();
        let lhs = self.stack.pop().unwrap();
        self.stack.push(lhs * rhs);
    }

    /// Runs the `or` operation.
    pub fn or(&mut self) {
        let rhs = self.stack.pop().unwrap();
        let lhs = self.stack.pop().unwrap();
        self.stack.push(lhs + rhs);
    }

    /// Negates what's in the builder stack.
    pub fn neg(&mut self) {
        let value = self.stack.pop().unwrap();
        self.stack.push(-value);
    }

    /// Runs the `and` operation until there is only one element left in the stack.
    pub fn finalize_and(&mut self) {
        while self.stack.len() > 1 {
            self.and();
        }
    }

    /// Build the selection and returns it.
    pub fn build(mut self) -> Selection {
        assert_eq!(self.stack.len(), 1);
        self.stack.pop().unwrap()
    }
}

impl<'a> QueryBuilder<'a> {
    /// Constructs a new query builder that belongs to the given IRBuilder.
    pub fn new(ir_builder: &'a IRBuilder) -> QueryBuilder<'a> {
        QueryBuilder {
            builder: ir_builder,
            parameters: Vec::new(),
            current_selection: SelectionBuilder::new(),
        }
    }

    /// Adds a parameter to this query.
    pub fn parameter(&mut self, name: String, type_name: &String, nullable: bool) {
        let ir_type = self.builder.get_type(type_name);
        self.parameters.push((name, ir_type, nullable));
    }

    /// Add a is pipeline to the query.
    pub fn is(&mut self, type_name: &String) {
        let type_id = self.builder.resolve_type_id(type_name);
        self.current_selection.is(type_id);
    }
}

impl ActionBuilder {
    pub fn new() -> ActionBuilder {
        ActionBuilder {}
    }
}
