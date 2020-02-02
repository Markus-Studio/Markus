#![allow(dead_code)]
use std::collections::HashMap;

type TypeId = u32;
type FieldId = u32;

pub struct MarkusObjectTypeField {
    name: FieldId,
    field_type: TypeId,
}

pub enum MarkusTypeInfo {
    Union {
        members: Vec<TypeId>,
    },
    Object {
        parents: Vec<TypeId>,
        fields: Vec<MarkusObjectTypeField>,
    },
    None,
}

pub enum MarkusTypeKind {
    Atomic,
    Never,
    ObjectOrUnion,
}

pub struct MarkusType {
    pub id: TypeId,
    pub is_array_of: bool,
    pub kind: MarkusTypeKind,
    pub type_info: MarkusTypeInfo,
}

pub struct TypeSpace {
    type_names: HashMap<String, TypeId>,
    field_names: HashMap<String, FieldId>,
    last_type_id: TypeId,
    last_field_id: TypeId,
    types: HashMap<TypeId, MarkusType>,
}

impl<'a> TypeSpace {
    pub fn new() -> TypeSpace {
        TypeSpace {
            type_names: HashMap::new(),
            field_names: HashMap::new(),
            last_type_id: 0,
            last_field_id: 0,
            types: HashMap::new(),
        }
    }

    pub fn new_with_builtins() -> TypeSpace {
        let space = TypeSpace::new();

        space
    }

    /// Returns a new type id to be used in a new type with the given name.
    #[inline]
    pub fn get_new_type_id(&mut self, name: &str) -> TypeId {
        match self.resolve_type_id(name) {
            Some(id) => *id,
            None => {
                let id = self.last_type_id;
                self.last_type_id += 1;
                self.type_names.insert(String::from(name), id);
                id
            }
        }
    }

    #[inline]
    pub fn get_new_field_id(&mut self, name: &str) -> TypeId {
        match self.resolve_field_id(name) {
            Some(id) => *id,
            None => {
                let id = self.last_field_id;
                self.last_field_id += 1;
                self.field_names.insert(String::from(name), id);
                id
            }
        }
    }

    #[inline(always)]
    pub fn resolve_field_id(&self, name: &str) -> Option<&u32> {
        self.field_names.get(name)
    }

    #[inline(always)]
    pub fn resolve_type_id(&self, name: &str) -> Option<&u32> {
        self.type_names.get(name)
    }

    #[inline(always)]
    pub fn resolve_type_by_id(&self, id: TypeId) -> Option<&MarkusType> {
        self.types.get(&id)
    }

    #[inline(always)]
    pub fn resolve_type(&self, name: &str) -> Option<&MarkusType> {
        match self.resolve_type_id(name) {
            Some(&id) => self.resolve_type_by_id(id),
            None => None,
        }
    }

    /// Returns whatever a type with the given name exists in this type space.
    pub fn exists(&self, type_name: &str) -> bool {
        match self.resolve_type(type_name) {
            Some(_) => true,
            None => false,
        }
    }

    /// Removes the given type from this type space.
    pub fn remove(&mut self, type_name: &str) {
        match self.resolve_type_id(type_name) {
            Some(&id) => {
                self.types.remove(&id);
            }
            _ => {}
        }
    }

    pub fn define_type(&mut self, name: &str, markus_type: MarkusType) {
        let id = self.resolve_type_id(name).unwrap();
        assert_eq!(markus_type.id, id);
    }

    /// Returns the result of evaluating "`lhs` is `rhs`"
    pub fn is(&self, lhs: &MarkusType, rhs: &MarkusType) -> bool {
        panic!("Not implemented.");
    }

    /// Returns whatever the given field exists on the base type.
    pub fn has(&self, base: &MarkusType, uri: Vec<&str>) -> bool {
        panic!("Not implemented.");
    }
}

impl MarkusType {
    pub fn new_atomic(space: &mut TypeSpace, name: &str) {}
}
