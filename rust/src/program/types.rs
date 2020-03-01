use crate::parser::ast::TypeDeclarationNode;
use crate::program::Diagnostic;
use bimap::BiMap;
use std::collections::{HashMap, HashSet, VecDeque};
use std::rc::Rc;

/// A type id is basically a map from an string to an integer unique to
/// every type space, it is used to prevent copying tons of strings.
pub type TypeId = u32;

#[derive(Clone, Debug)]
pub enum MarkusTypeInfo {
    Atomic {
        id: TypeId,
        name: String,
    },
    Union {
        members: HashSet<TypeId>,
    },
    OneOf {
        id: TypeId,
        name: String,
        cases: HashSet<TypeId>,
    },
    BuiltInObject {
        id: TypeId,
        bases: HashSet<TypeId>,
        fields: HashMap<String, HashSet<TypeId>>,
    },
    Object {
        id: TypeId,
        ast: Rc<TypeDeclarationNode>,
    },
}

#[derive(Clone)]
pub struct MarkusType {
    /// This value indicates dimension of the actual type, a type such as
    /// `x` where x is an atomic is considered a 0-dimensional type while
    /// `x[]` and `x[][]` are true and 2-dimensional accordingly.
    pub dimension: u32,
    pub type_info: MarkusTypeInfo,
}

pub struct TypeSpace {
    type_names: BiMap<String, TypeId>,
    pub types: HashMap<TypeId, MarkusType>,
    last_type_id: TypeId,
}

impl TypeSpace {
    /// Creates a new empty type space.
    pub fn new() -> TypeSpace {
        TypeSpace {
            type_names: BiMap::new(),
            types: HashMap::new(),
            last_type_id: 1,
        }
    }

    /// Creates a new type space containing builtin Markus types.
    pub fn new_with_builtins() -> TypeSpace {
        let mut space = TypeSpace::new();
        let i32_id = space.define_atomic("i32");
        let i64_id = space.define_atomic("i64");
        let u32_id = space.define_atomic("u32");
        let u64_id = space.define_atomic("u64");
        let f32_id = space.define_atomic("f32");
        let f64_id = space.define_atomic("f64");
        space.define_atomic("string");
        space.define_atomic("bool");
        space.define_atomic("time");
        space.define_atomic("null");
        space.define_builtin_object("user", vec![], vec![]);
        // space.define_builtin_object(
        //     "geo",
        //     vec![],
        //     vec![
        //         (
        //             String::from("lat"),
        //             vec![f32_id].iter().map(|s| *s).collect(),
        //         ),
        //         (
        //             String::from("long"),
        //             vec![f32_id].iter().map(|s| *s).collect(),
        //         ),
        //     ],
        // );
        space.define_one_of("%unsigned-int", vec![u32_id, u64_id]);
        space.define_one_of("%neg-int", vec![i32_id, i64_id]);
        space.define_one_of("%int", vec![i32_id, i64_id, u32_id, u64_id]);
        space.define_one_of("%float", vec![f32_id, f64_id]);
        space.define_one_of(
            "%number",
            vec![i32_id, i64_id, u32_id, u64_id, f32_id, f64_id],
        );
        space
    }

    /// Returns the type id for the given name or creates a new one.
    fn get_type_id_or_create(&mut self, name: &str) -> TypeId {
        match self.type_names.get_by_left(&String::from(name)) {
            Some(&id) => id,
            _ => {
                let id = self.last_type_id;
                self.last_type_id += 1;
                self.type_names.insert(String::from(name), id);
                id
            }
        }
    }

    /// Inserts the given type to the current type space.
    #[inline(always)]
    fn define_type(&mut self, id: TypeId, markus_type: MarkusType) {
        match self.types.insert(id, markus_type) {
            Some(_) => {
                panic!("Name already in use.");
            }
            _ => {}
        }
    }

    pub fn define_map(&mut self, key: MarkusType, value: MarkusType) -> MarkusType {
        let name = format!("Map({}, {})", key.to_string(self), value.to_string(self));
        if !self.contains(&name) {
            self.define_builtin_object(
                &name,
                Vec::with_capacity(0),
                vec![
                    (String::from("key"), key.get_ids_set()),
                    (String::from("value"), value.get_ids_set()),
                ],
            );
        }

        self.resolve_type(&name).unwrap().clone()
    }

    #[inline]
    pub fn get_type_name(&self, id: TypeId) -> String {
        self.type_names.get_by_right(&id).unwrap().to_string()
    }

    /// Defines a new atomic type in this type space.
    pub fn define_atomic(&mut self, name: &str) -> TypeId {
        let id = self.get_type_id_or_create(name);
        let markus_type = MarkusType {
            dimension: 0,
            type_info: MarkusTypeInfo::Atomic {
                id,
                name: String::from(name),
            },
        };
        self.define_type(id, markus_type);
        id
    }

    /// Defines a new builtin one-of type in this type space.
    pub fn define_one_of(&mut self, name: &str, cases: Vec<TypeId>) -> TypeId {
        let id = self.get_type_id_or_create(name);
        let markus_type = MarkusType {
            dimension: 0,
            type_info: MarkusTypeInfo::OneOf {
                id,
                name: String::from(name),
                cases: cases.into_iter().collect(),
            },
        };
        self.define_type(id, markus_type);
        id
    }

    /// Defines a new builtin object type in this type space.
    pub fn define_builtin_object(
        &mut self,
        name: &str,
        bases: Vec<&str>,
        fields: Vec<(String, HashSet<TypeId>)>,
    ) -> TypeId {
        let id = self.get_type_id_or_create(name);
        let markus_type = MarkusType {
            dimension: 0,
            type_info: MarkusTypeInfo::BuiltInObject {
                id,
                bases: bases
                    .into_iter()
                    .map(|base_name| self.resolve_type(base_name).unwrap().get_id())
                    .collect(),
                fields: fields.into_iter().collect(),
            },
        };
        self.define_type(id, markus_type);
        id
    }

    /// Finds the type with the given id and returns it.
    #[inline]
    pub fn resolve_type_by_id(&self, id: TypeId) -> Option<&MarkusType> {
        self.types.get(&id)
    }

    /// Finds the type with the given name and returns it.
    #[inline]
    pub fn resolve_type(&self, name: &str) -> Option<&MarkusType> {
        match self.type_names.get_by_left(&String::from(name)) {
            Some(&id) => self.resolve_type_by_id(id),
            None => None,
        }
    }

    /// Returns true if a type with the given name exists in this type space.
    #[inline]
    pub fn contains(&self, name: &str) -> bool {
        match self.type_names.get_by_left(&String::from(name)) {
            Some(id) => match self.types.get(id) {
                Some(_) => true,
                _ => false,
            },
            _ => false,
        }
    }

    /// Adds the given type to this type space.
    pub fn add_type(&mut self, ast: Rc<TypeDeclarationNode>) {
        if let Some(name_identifier) = &ast.name {
            let name = &name_identifier.value;
            let id = self.get_type_id_or_create(name);
            let markus_type = MarkusType {
                dimension: 0,
                type_info: MarkusTypeInfo::Object { id, ast },
            };
            self.define_type(id, markus_type)
        }
    }

    /// Verifies the current type space returns a vector containing all of the
    /// errors found on types.
    pub fn verify(&self, diagnostics: &mut Vec<Diagnostic>) {
        for markus_type in self.types.values() {
            match markus_type.type_info {
                MarkusTypeInfo::Object { .. } => {
                    markus_type.object_verify(self, diagnostics);
                }
                _ => {}
            }
        }
    }

    /// Returns a 1D Union that contains every user defined object types.
    pub fn get_query_input_type(&self) -> MarkusType {
        let mut members: HashSet<TypeId> = HashSet::with_capacity(self.types.len());

        for markus_type in self.types.values() {
            match markus_type.type_info {
                MarkusTypeInfo::Object { .. } => {
                    members.insert(markus_type.get_id());
                }
                _ => {}
            }
        }

        MarkusType {
            dimension: 1, // It's an array.
            type_info: MarkusTypeInfo::Union { members: members },
        }
    }

    /// Returns a Union that contains every user defined object types that extends `user`.
    pub fn get_permission_input_type(&self) -> MarkusType {
        let mut members: HashSet<TypeId> = HashSet::with_capacity(self.types.len());
        let user = self.resolve_type("user").unwrap();

        for markus_type in self.types.values() {
            match markus_type.type_info {
                MarkusTypeInfo::Object { .. } => {
                    if markus_type.is(self, user) {
                        members.insert(markus_type.get_id());
                    }
                }
                _ => {}
            }
        }

        MarkusType {
            dimension: 0,
            type_info: MarkusTypeInfo::Union { members: members },
        }
    }
}

impl MarkusType {
    /// Creates a new union with the given members and returns it.
    pub fn new_union(members: Vec<TypeId>) -> MarkusType {
        MarkusType {
            dimension: 0,
            type_info: MarkusTypeInfo::Union {
                members: members.into_iter().collect(),
            },
        }
    }

    /// Returns true if the current type is nil.
    pub fn is_nil(&self) -> bool {
        match self.type_info {
            MarkusTypeInfo::Union { ref members } => members.len() == 0,
            _ => false,
        }
    }

    /// Returns true if the current type is an object type.
    pub fn is_object(&self) -> bool {
        match self.type_info {
            MarkusTypeInfo::Object { .. } => true,
            MarkusTypeInfo::BuiltInObject { .. } => true,
            _ => false,
        }
    }

    /// Returns the result of evaluating `self is rhs`.
    pub fn is(&self, space: &TypeSpace, rhs: &MarkusType) -> bool {
        if self.dimension != rhs.dimension {
            return false;
        }

        match (&self.type_info, &rhs.type_info) {
            (MarkusTypeInfo::OneOf { cases, .. }, _) => {
                for case_id in cases {
                    let case = space.resolve_type_by_id(*case_id).unwrap();
                    if case.is(space, rhs) {
                        return true;
                    }
                }
                false
            }
            (_, MarkusTypeInfo::OneOf { cases, .. }) => {
                for case_id in cases {
                    let case = space.resolve_type_by_id(*case_id).unwrap();
                    if self.is(space, case) {
                        return true;
                    }
                }
                false
            }
            (
                MarkusTypeInfo::Atomic { id: ref lhs_id, .. },
                MarkusTypeInfo::Atomic { id: ref rhs_id, .. },
            ) => {
                // Two atomic types are considered to be same if and only if
                // they share the same id.
                lhs_id == rhs_id
            }
            (MarkusTypeInfo::Atomic { ref id, .. }, MarkusTypeInfo::Union { ref members }) => {
                // `x is T: {A, B, ...}` holds true for all x-es that are in the T.
                for member in members {
                    if member == id {
                        return true;
                    }

                    let resolved_type = space.resolve_type_by_id(*member).unwrap();
                    match resolved_type.type_info {
                        MarkusTypeInfo::OneOf { .. } => {
                            if self.is(space, resolved_type) {
                                return true;
                            }
                        }
                        _ => {}
                    }
                }
                false
            }
            (MarkusTypeInfo::Atomic { .. }, _) => {
                // An atomic type is only assignable to another atomic.
                false
            }
            (MarkusTypeInfo::Union { ref members }, MarkusTypeInfo::Atomic { ref id, .. }) => {
                // `T: {A, B, ...} is x` if and only if T = {x}
                if members.len() != 1 {
                    return false;
                }

                let mut iter = members.iter();
                let member = iter.next().unwrap();

                if member == id {
                    return true;
                }

                let resolved_type = space.resolve_type_by_id(*member).unwrap();
                match resolved_type.type_info {
                    MarkusTypeInfo::OneOf { .. } => {
                        if resolved_type.is(space, rhs) {
                            return true;
                        }
                    }
                    _ => {}
                }

                false
            }
            (MarkusTypeInfo::Union { ref members }, MarkusTypeInfo::Object { .. })
            | (MarkusTypeInfo::Union { ref members }, MarkusTypeInfo::BuiltInObject { .. })
            | (MarkusTypeInfo::Union { ref members }, MarkusTypeInfo::Union { .. }) => {
                if members.len() == 0 {
                    false
                } else {
                    for &type_id in members {
                        let member = space.resolve_type_by_id(type_id).unwrap();
                        if !member.is(space, rhs) {
                            return false;
                        }
                    }
                    true
                }
            }
            (MarkusTypeInfo::Object { .. }, MarkusTypeInfo::Object { ref id, .. })
            | (MarkusTypeInfo::Object { .. }, MarkusTypeInfo::BuiltInObject { ref id, .. })
            | (MarkusTypeInfo::BuiltInObject { .. }, MarkusTypeInfo::Object { ref id, .. })
            | (
                MarkusTypeInfo::BuiltInObject { .. },
                MarkusTypeInfo::BuiltInObject { ref id, .. },
            ) => {
                // `o1: {all_parents} is o2` is true for all such that o2 is a member of all_parents.
                if self.get_id() == *id {
                    return true;
                }

                for base_id in self.object_bases_recursive(space) {
                    if base_id == *id {
                        return true;
                    }
                }
                false
            }
            (MarkusTypeInfo::Object { .. }, MarkusTypeInfo::Union { ref members })
            | (MarkusTypeInfo::BuiltInObject { .. }, MarkusTypeInfo::Union { ref members }) => {
                for &type_id in members {
                    let member = space.resolve_type_by_id(type_id).unwrap();
                    if self.is(space, member) {
                        return true;
                    }
                }
                false
            }
            (MarkusTypeInfo::Object { .. }, MarkusTypeInfo::Atomic { .. })
            | (MarkusTypeInfo::BuiltInObject { .. }, MarkusTypeInfo::Atomic { .. }) => false,
        }
    }

    /// Returns the id of the current type.
    /// # Panics
    /// If the type is an union and has no id.
    pub fn get_id(&self) -> TypeId {
        match self.type_info {
            MarkusTypeInfo::Atomic { id, .. } => id,
            MarkusTypeInfo::BuiltInObject { id, .. } => id,
            MarkusTypeInfo::Object { id, .. } => id,
            MarkusTypeInfo::OneOf { id, .. } => id,
            MarkusTypeInfo::Union { .. } => panic!("An union type has no id."),
        }
    }

    /// Creates an union from all of the types in the given vector.
    /// # Panics
    /// If the types vector is empty or if the given types are not of the same dimension.
    pub fn create_union_from(types: Vec<MarkusType>) -> MarkusType {
        match types.len() {
            0 => MarkusType::new_union(Vec::with_capacity(0)),
            1 => types[0].clone(),
            len => {
                let mut result: MarkusType = types[0].clone();
                for i in 1..len {
                    result = result + &types[i];
                }
                result
            }
        }
    }

    /// Returns the current type but with the request dimension.
    pub fn with_dimension(&self, dimension: u32) -> MarkusType {
        MarkusType {
            dimension,
            type_info: self.type_info.clone(),
        }
    }

    /// Filters the current type to contain only those that are extended of
    /// the base, it's actually result of the `is(base)` pipeline.
    pub fn filter(&self, space: &TypeSpace, base: &MarkusType, neg: bool) -> MarkusType {
        let mut members: HashSet<TypeId> = HashSet::new();

        match &self.type_info {
            MarkusTypeInfo::Atomic { id, .. }
            | MarkusTypeInfo::BuiltInObject { id, .. }
            | MarkusTypeInfo::Object { id, .. } => {
                let check = self.is(space, base);
                if if neg { !check } else { check } {
                    members.insert(*id);
                }
            }
            MarkusTypeInfo::Union {
                members: union_members,
                ..
            } => {
                for member in union_members {
                    let check = space.resolve_type_by_id(*member).unwrap().is(space, base);
                    if if neg { !check } else { check } {
                        members.insert(*member);
                    }
                }
            }
            MarkusTypeInfo::OneOf { .. } => {
                panic!("Filter is not meant to be used with `OneOf` type.")
            }
        }

        MarkusType {
            dimension: self.dimension,
            type_info: MarkusTypeInfo::Union { members },
        }
    }

    /// Return true if the value of the given field might be null.
    pub fn is_nullable(&self, space: &TypeSpace, uri: &[&str]) -> bool {
        match &self.type_info {
            MarkusTypeInfo::BuiltInObject { .. } => false,
            MarkusTypeInfo::Object { .. } => self.object_is_nullable(space, uri),
            MarkusTypeInfo::Union { members } => {
                for &id in members {
                    match space
                        .resolve_type_by_id(id)
                        .unwrap()
                        .is_nullable(space, uri)
                    {
                        true => return true,
                        false => {}
                    }
                }

                return false;
            }
            _ => unimplemented!(),
        }
    }

    /// Queries the given URI on the current type, returns `None` if
    /// the field did not existed on the current object.
    pub fn query(&self, space: &TypeSpace, uri: &[&str]) -> Option<MarkusType> {
        match &self.type_info {
            MarkusTypeInfo::Atomic { .. } => None,
            MarkusTypeInfo::OneOf { .. } => {
                // TODO(qti3e).
                panic!("Type query for `OneOf` is not implemented.")
            }
            MarkusTypeInfo::BuiltInObject { .. } | MarkusTypeInfo::Object { .. } => {
                self.object_query(space, uri)
            }
            MarkusTypeInfo::Union { members } => {
                if members.len() == 0 {
                    return None;
                }

                let mut dimension = std::u32::MAX;
                let mut new_members: HashSet<TypeId> = HashSet::new();
                for member in members {
                    match space.resolve_type_by_id(*member).unwrap().query(space, uri) {
                        Some(data_type) => {
                            if dimension == std::u32::MAX {
                                dimension = data_type.dimension;
                            } else if dimension != data_type.dimension {
                                return None;
                            }

                            match &data_type.type_info {
                                MarkusTypeInfo::Atomic { id, .. }
                                | MarkusTypeInfo::BuiltInObject { id, .. }
                                | MarkusTypeInfo::Object { id, .. } => {
                                    new_members.insert(*id);
                                }
                                MarkusTypeInfo::Union { members: u_members } => {
                                    new_members.extend(u_members.iter());
                                }
                                _ => {}
                            }
                        }
                        None => {
                            return None;
                        }
                    }
                }

                Some(MarkusType {
                    dimension,
                    type_info: MarkusTypeInfo::Union {
                        members: new_members,
                    },
                })
            }
        }
    }
}

impl MarkusType {
    /// Returns a set containing direct bases of the current object.
    /// # Panics
    /// If the current type is not an object.
    pub fn object_bases(&self, space: &TypeSpace) -> HashSet<TypeId> {
        match &self.type_info {
            MarkusTypeInfo::Object { ref ast, .. } => {
                let mut result: HashSet<TypeId> = HashSet::with_capacity(ast.bases.len());
                for base in &ast.bases {
                    if let Some(markus_type) = space.resolve_type(&base.value) {
                        result.insert(markus_type.get_id());
                    }
                }
                result
            }
            MarkusTypeInfo::BuiltInObject { bases, .. } => bases.clone(),
            _ => panic!("object_* is only for object types."),
        }
    }

    /// Returns a set containing all of the bases of the current object recursively.
    pub fn object_bases_recursive(&self, space: &TypeSpace) -> HashSet<TypeId> {
        // TODO(qti3e) We need to somehow cache this.
        let mut result: HashSet<TypeId> = HashSet::new();
        result.insert(self.get_id());
        object_collect_bases(&mut result, space, self);
        result.remove(&self.get_id());
        result
    }

    /// Returns true if the current object owns a field with the given name.
    pub fn object_owns(&self, field_name: &str) -> bool {
        match self.type_info {
            MarkusTypeInfo::BuiltInObject { ref fields, .. } => fields.get(field_name) != None,
            MarkusTypeInfo::Object { ref ast, .. } => {
                for field in &ast.fields {
                    match &field.name {
                        Some(identifier) if identifier.value == field_name => return true,
                        _ => {}
                    }
                }
                false
            }
            _ => panic!("object_owns is only for object types."),
        }
    }

    /// Returns true if a field with the given name exists in the current object.
    pub fn object_has_field(&self, space: &TypeSpace, field_name: &str) -> bool {
        // TODO(qti3e) Optimize this function (maybe use a HashMap?)
        if self.object_owns(field_name) {
            return true;
        }

        for &base_id in self.object_bases_recursive(space).iter() {
            let base = space.resolve_type_by_id(base_id).unwrap();
            if base.object_owns(field_name) {
                return true;
            }
        }

        false
    }

    /// Queries the type of given filed on this object recursively.
    /// # Panics
    /// If the current type is not an object.
    #[inline]
    fn object_query_field(
        &self,
        space: &TypeSpace,
        field_name: &str,
    ) -> Option<(MarkusType, bool)> {
        match self.type_info {
            MarkusTypeInfo::BuiltInObject { ref fields, .. } => match fields.get(field_name) {
                Some(type_ids) => {
                    let ids: Vec<TypeId> = type_ids.iter().map(|s| *s).collect();
                    Some((MarkusType::new_union(ids), false))
                }
                None => None,
            },
            MarkusTypeInfo::Object { ref ast, .. } => {
                for field in &ast.fields {
                    match &field.name {
                        Some(identifier) if identifier.value == field_name => {
                            return match &field.type_name {
                                Some(type_identifier) => {
                                    match space.resolve_type(&type_identifier.value) {
                                        Some(markus_type) => {
                                            Some((markus_type.clone(), field.nullable))
                                        }
                                        None => None,
                                    }
                                }
                                None => None,
                            }
                        }
                        _ => {}
                    }
                }

                for &base_id in self.object_bases_recursive(space).iter() {
                    let base = space.resolve_type_by_id(base_id).unwrap();
                    if let Some(markus_type) = base.object_query_field(space, field_name) {
                        return Some(markus_type);
                    }
                }

                None
            }
            _ => panic!("object_query_field is only for object types."),
        }
    }

    /// # Panics
    /// If the current type is not an object.
    fn object_query(&self, space: &TypeSpace, uri: &[&str]) -> Option<MarkusType> {
        match uri.len() {
            0 => Some(self.clone()),
            1 => match self.object_query_field(space, uri[0]) {
                Some((field_type, _)) => Some(field_type),
                None => None,
            },
            _ => match self.object_query_field(space, uri[0]) {
                Some((field_type, _)) => field_type.object_query(space, &uri[1..]),
                None => None,
            },
        }
    }

    /// Returns true if the given field on current type might be null.
    /// # Panics
    /// If the current type is not an object.
    fn object_is_nullable(&self, space: &TypeSpace, uri: &[&str]) -> bool {
        match uri.len() {
            0 => false,
            1 => match self.object_query_field(space, uri[0]) {
                Some((_, nullable)) => nullable,
                None => false,
            },
            _ => match self.object_query_field(space, uri[0]) {
                Some((_, true)) => true,
                Some((field_type, _)) => field_type.object_is_nullable(space, &uri[1..]),
                None => false,
            },
        }
    }

    /// Verifies a user defined object type returns a vector containing all of
    /// the diagnostics found on this object, including:
    /// 1. Unresolved Names
    /// 2. Base not object.
    /// 3. Circular Reference (Both on fields and bases)
    /// 4. Common field.
    /// 5. Name already in use.
    pub fn object_verify(&self, space: &TypeSpace, diagnostics: &mut Vec<Diagnostic>) {
        match self.type_info {
            MarkusTypeInfo::Object { ref ast, .. } => verify_object_ast(ast, space, diagnostics),
            _ => panic!(
                "object_is_circular is only meant to be used with user defined object types."
            ),
        }
    }

    fn get_ids_set(&self) -> HashSet<TypeId> {
        let members: Vec<TypeId> = match &self.type_info {
            MarkusTypeInfo::OneOf { .. } => unimplemented!(),
            MarkusTypeInfo::Union { members, .. } => members.iter().map(|s| *s).collect(),
            _ => vec![self.get_id()],
        };
        members.iter().map(|s| *s).collect()
    }
}

impl std::ops::Add<&MarkusType> for MarkusType {
    type Output = MarkusType;

    fn add(self, rhs: &MarkusType) -> MarkusType {
        assert_eq!(self.dimension, rhs.dimension);

        let lhs_members: HashSet<TypeId> = self.get_ids_set();
        let rhs_members: HashSet<TypeId> = rhs.get_ids_set();

        let mut members = HashSet::with_capacity(lhs_members.len() + rhs_members.len());
        members.extend(lhs_members.iter());
        members.extend(rhs_members.iter());

        members.shrink_to_fit();

        MarkusType {
            dimension: self.dimension,
            type_info: MarkusTypeInfo::Union { members },
        }
    }
}

#[inline(always)]
fn verify_object_ast(
    ast: &Rc<TypeDeclarationNode>,
    space: &TypeSpace,
    diagnostics: &mut Vec<Diagnostic>,
) {
    for base_identifier in &ast.bases {
        let base_name = &base_identifier.value;
        // Try to resolve the name, report an error on failure.
        match space.resolve_type(base_name) {
            Some(base) if !base.is_object() => {
                // Base type must be also of object type.
                diagnostics.push(Diagnostic::base_not_object(base_identifier));
            }
            Some(base) => {
                // Try to find circular bases.
                if let Some(name_identifier) = &ast.name {
                    let mut seen: HashSet<TypeId> = HashSet::new();
                    let name = &name_identifier.value;
                    let current_id = space.resolve_type(name).unwrap().get_id();
                    seen.insert(current_id);
                    if is_circular(space, &mut seen, current_id, base) {
                        diagnostics.push(Diagnostic::circular_reference(base_identifier))
                    } else {
                        // Shared fields. (A name that is already present in the bases)
                        for field in &ast.fields {
                            if let Some(field_identifier) = &field.name {
                                if base.object_has_field(space, &field_identifier.value) {
                                    diagnostics
                                        .push(Diagnostic::name_already_in_use(field_identifier));
                                }
                            }
                        }
                    }
                }
            }
            _ => {
                // Report the error.
                diagnostics.push(Diagnostic::unresolved_name(base_identifier));
            }
        }
    }

    let mut seen_names: HashSet<String> = HashSet::with_capacity(ast.fields.len());
    for field in &ast.fields {
        if let Some(field_name_identifier) = &field.name {
            let field_name = &field_name_identifier.value;
            if seen_names.contains(field_name) {
                diagnostics.push(Diagnostic::name_already_in_use(&field_name_identifier));
            }

            seen_names.insert(field_name.clone());
        }

        match &field.type_name {
            Some(type_name_identifier) => {
                let type_name = &type_name_identifier.value;

                if !field.nullable {
                    if let Some(ast_type_name) = &ast.name {
                        if ast_type_name.value == *type_name {
                            diagnostics.push(Diagnostic::circular_reference(&type_name_identifier));
                        }
                    }
                }

                match space.resolve_type(type_name) {
                    None => {
                        // Unresolved name error.
                        diagnostics.push(Diagnostic::unresolved_name(&type_name_identifier));
                    }
                    _ => {}
                }
            }
            // Nothing.
            _ => {}
        }
    }
}

#[inline]
fn is_circular(
    space: &TypeSpace,
    seen: &mut HashSet<TypeId>,
    stop: TypeId,
    visit: &MarkusType,
) -> bool {
    for base_id in visit.object_bases(space) {
        if base_id == stop {
            return true;
        }

        // Here we don't actually care about other types being circular, just
        // find circular paths that ends with `stop`, but also we don't wanna
        // get stuck in an infinite loop here.
        if !seen.insert(base_id) {
            continue;
        }

        seen.insert(base_id);

        if is_circular(
            space,
            seen,
            stop,
            space.resolve_type_by_id(base_id).unwrap(),
        ) {
            return true;
        }
    }
    false
}

#[inline]
fn object_collect_bases(collected: &mut HashSet<TypeId>, space: &TypeSpace, object: &MarkusType) {
    let mut to_visit: VecDeque<TypeId> = object.object_bases(space).into_iter().collect();
    collected.reserve(to_visit.len());
    while let Some(id) = to_visit.pop_front() {
        if collected.insert(id) {
            // Now we need to add id.parents to the to_visit.
            match space.resolve_type_by_id(id) {
                Some(markus_type) => {
                    object_collect_bases(collected, space, markus_type);
                }
                None => {}
            }
        }
    }
}

impl MarkusType {
    pub fn to_string(&self, space: &TypeSpace) -> String {
        let mut type_str = match &self.type_info {
            MarkusTypeInfo::Atomic { id, .. }
            | MarkusTypeInfo::BuiltInObject { id, .. }
            | MarkusTypeInfo::OneOf { id, .. }
            | MarkusTypeInfo::Object { id, .. } => space.get_type_name(*id),
            MarkusTypeInfo::Union { members, .. } => match members.len() {
                0 => String::from("ø"),
                1 => space.get_type_name(*members.iter().next().unwrap()),
                _ => {
                    let mut result = String::from("(");
                    for (index, member) in members.iter().enumerate() {
                        if index > 0 {
                            result.push_str(" | ")
                        }
                        result.push_str(&space.get_type_name(*member));
                    }
                    result.push_str(")");
                    result
                }
            },
        };

        for _ in 0..self.dimension {
            type_str.push_str("[]");
        }

        type_str
    }
}

#[test]
fn is() {
    let mut space = TypeSpace::new();
    let x_id = space.define_atomic("x");
    let y_id = space.define_atomic("y");
    let z_id = space.define_atomic("z");

    let d_id = space.define_builtin_object("D", vec![], vec![]);
    let c_id = space.define_builtin_object("C", vec!["D"], vec![]);
    let b_id = space.define_builtin_object("B", vec![], vec![]);
    let a_id = space.define_builtin_object("A", vec!["B", "C"], vec![]);
    let e_id = space.define_builtin_object("E", vec!["C"], vec![]);
    let f_id = space.define_builtin_object("F", vec!["E"], vec![]);
    let j_id = space.define_builtin_object("J", vec!["F"], vec![]);
    let m_id = space.define_builtin_object("M", vec![], vec![]);
    let l_id = space.define_builtin_object("L", vec![], vec![]);

    // ø
    let empty = MarkusType::new_union(vec![]);
    // x | y
    let x_or_y = MarkusType::new_union(vec![x_id, y_id]);
    // y | z
    let y_or_z = MarkusType::new_union(vec![y_id, z_id]);
    // x | y | A
    let x_or_y_or_a = MarkusType::new_union(vec![x_id, y_id, a_id]);
    // A | L
    let a_or_l = MarkusType::new_union(vec![a_id, l_id]);
    // L | M
    let l_or_m = MarkusType::new_union(vec![l_id, m_id]);
    // B | C
    let b_or_c = MarkusType::new_union(vec![b_id, c_id]);
    // C | D
    let c_or_d = MarkusType::new_union(vec![c_id, d_id]);
    // x | A
    let x_or_a = MarkusType::new_union(vec![x_id, a_id]);
    // x | B
    let x_or_b = MarkusType::new_union(vec![x_id, b_id]);
    // x | A | L
    let x_or_a_or_l = MarkusType::new_union(vec![x_id, a_id, l_id]);

    let x = space.resolve_type("x").unwrap();
    let y = space.resolve_type("y").unwrap();
    let z = space.resolve_type("z").unwrap();

    let a = space.resolve_type_by_id(a_id).unwrap();
    let b = space.resolve_type_by_id(b_id).unwrap();
    let c = space.resolve_type_by_id(c_id).unwrap();
    let d = space.resolve_type_by_id(d_id).unwrap();
    let e = space.resolve_type_by_id(e_id).unwrap();
    let f = space.resolve_type_by_id(f_id).unwrap();
    let j = space.resolve_type_by_id(j_id).unwrap();
    let l = space.resolve_type_by_id(l_id).unwrap();

    assert_eq!(x.is(&space, x), true);
    assert_eq!(x.is(&space, y), false);
    assert_eq!(x.is(&space, &x_or_y), true);
    assert_eq!(x.is(&space, &y_or_z), false);
    assert_eq!(x.is(&space, &x_or_y_or_a), true);
    assert_eq!(x.is(&space, &empty), false);

    assert_eq!(a.is(&space, a), true);
    assert_eq!(a.is(&space, b), true);
    assert_eq!(b.is(&space, a), false);
    assert_eq!(b.is(&space, c), false);
    assert_eq!(a.is(&space, d), true);
    assert_eq!(a.is(&space, l), false);
    assert_eq!(a.is(&space, &a_or_l), true);
    assert_eq!(a.is(&space, &x_or_a), true);
    assert_eq!(a.is(&space, &x_or_a_or_l), true);
    assert_eq!(a.is(&space, &l_or_m), false);
    assert_eq!(a.is(&space, &b_or_c), true);
    assert_eq!(a.is(&space, &c_or_d), true);
    assert_eq!(a.is(&space, &x_or_y_or_a), true);
    assert_eq!(a.is(&space, &empty), false);
    assert_eq!(j.is(&space, d), true);

    assert_eq!(y.is(&space, &x_or_y), true);
    assert_eq!(y.is(&space, &empty), false);
    assert_eq!(y.is(&space, &x_or_y_or_a), true);
    assert_eq!(y.is(&space, x), false);
    assert_eq!(y.is(&space, z), false);

    assert_eq!(a.is(&space, &x_or_a), true);
    assert_eq!(a.is(&space, x), false);
    assert_eq!(a.is(&space, &x_or_b), true);
    assert_eq!(a.is(&space, &x_or_a_or_l), true);

    assert_eq!(e.is(&space, c), true);
    assert_eq!(f.is(&space, e), true);
    assert_eq!(l.is(&space, c), false);
    assert_eq!(b.is(&space, c), false);
    assert_eq!(b.is(&space, &b_or_c), true);
    assert_eq!(c.is(&space, a), false);
}
