#![allow(dead_code)]
use crate::parser::ast::TypeDeclarationNode;
use std::collections::HashMap;
use std::rc::Rc;

type TypeId = u32;

#[derive(Clone)]
pub struct MarkusObjectTypeField {
    name: String,
    field_type: TypeId,
}

#[derive(Clone)]
pub enum MarkusTypeInfo {
    Atomic,
    Never,
    Union {
        members: Vec<TypeId>,
    },
    BuiltInObject {
        parents: Vec<TypeId>,
        fields: Vec<MarkusObjectTypeField>,
    },
    Object {
        ast: Rc<TypeDeclarationNode>,
    },
}

#[derive(Clone)]
pub struct MarkusType {
    pub id: TypeId,
    /// This value indicates dimension of the actual type, a type such as
    /// `x` where x is an atomic is considered a 0-dimensional type while
    /// `x[]` and `x[][]` are 1 and 2-dimensional accordingly.
    pub dimension: u32,
    pub type_info: MarkusTypeInfo,
}

pub struct TypeSpace {
    type_names: HashMap<String, TypeId>,
    last_type_id: TypeId,
    types: HashMap<TypeId, MarkusType>,
}

impl<'a> TypeSpace {
    pub fn new() -> TypeSpace {
        TypeSpace {
            type_names: HashMap::new(),
            last_type_id: 1, // 0 is reserved for anonymous types.
            types: HashMap::new(),
        }
    }

    /// Creates a new type space with Markus Builtin types in it.
    pub fn new_with_builtins() -> TypeSpace {
        let mut space = TypeSpace::new();
        MarkusType::define_atomic(&mut space, "i32");
        MarkusType::define_atomic(&mut space, "i64");
        MarkusType::define_atomic(&mut space, "u32");
        MarkusType::define_atomic(&mut space, "u64");
        let f32_id = MarkusType::define_atomic(&mut space, "f32");
        MarkusType::define_atomic(&mut space, "f64");
        MarkusType::define_atomic(&mut space, "string");
        MarkusType::define_atomic(&mut space, "boolean");
        MarkusType::define_atomic(&mut space, "time");
        MarkusType::define_builtin_object(&mut space, "user", vec![], vec![]);
        MarkusType::define_builtin_object(
            &mut space,
            "geo",
            vec![],
            vec![
                MarkusObjectTypeField {
                    name: String::from("lat"),
                    field_type: f32_id,
                },
                MarkusObjectTypeField {
                    name: String::from("long"),
                    field_type: f32_id,
                },
            ],
        );
        space
    }

    /// Returns a new type id to be used in a new type with the given name.
    #[inline]
    pub fn get_new_type_id(&mut self, name: &str) -> TypeId {
        debug_assert!(name.len() > 0);
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
        let id = *self.resolve_type_id(name).unwrap();
        assert_eq!(markus_type.id, id);
        match self.types.insert(id, markus_type) {
            Some(_) => {
                panic!("Name already in use.");
            }
            None => {}
        }
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
    /// Define an atomic type with the given name on the given type space.
    pub fn define_atomic(space: &mut TypeSpace, name: &str) -> TypeId {
        let id = space.get_new_type_id(name);
        space.define_type(
            name,
            MarkusType {
                id: id,
                dimension: 0,
                type_info: MarkusTypeInfo::Atomic,
            },
        );
        id
    }

    /// Define a built in object type on the type space.
    pub fn define_builtin_object(
        space: &mut TypeSpace,
        name: &str,
        parents: Vec<&str>,
        fields: Vec<MarkusObjectTypeField>,
    ) -> TypeId {
        let id = space.get_new_type_id(name);
        let mut bases: Vec<TypeId> = Vec::with_capacity(parents.len());

        for base_name in parents {
            let base_id = *space.resolve_type_id(base_name).unwrap();
            bases.push(base_id);
        }

        space.define_type(
            name,
            MarkusType {
                id: id,
                dimension: 0,
                type_info: MarkusTypeInfo::BuiltInObject {
                    parents: bases,
                    fields: fields,
                },
            },
        );
        id
    }

    /// Creates a new empty union.
    pub fn new_union() -> MarkusType {
        MarkusType {
            id: 0,
            dimension: 0,
            type_info: MarkusTypeInfo::Union { members: vec![] },
        }
    }

    /// Add a member to a union type.
    pub fn union_add_member(&mut self, id: TypeId) {
        match self.type_info {
            MarkusTypeInfo::Union { ref mut members } => {
                members.push(id);
            }
            _ => panic!("union_add_member is only for union types."),
        }
    }
}

#[test]
fn test_is() {
    let mut space = TypeSpace::new();
    let x_id = MarkusType::define_atomic(&mut space, "x");
    let y_id = MarkusType::define_atomic(&mut space, "y");
    let z_id = MarkusType::define_atomic(&mut space, "z");

    let d_id = MarkusType::define_builtin_object(&mut space, "D", vec![], vec![]);
    let c_id = MarkusType::define_builtin_object(&mut space, "C", vec!["D"], vec![]);
    let b_id = MarkusType::define_builtin_object(&mut space, "B", vec![], vec![]);
    let a_id = MarkusType::define_builtin_object(&mut space, "A", vec!["B", "C"], vec![]);
    let e_id = MarkusType::define_builtin_object(&mut space, "E", vec!["C"], vec![]);
    let f_id = MarkusType::define_builtin_object(&mut space, "F", vec!["E"], vec![]);
    let j_id = MarkusType::define_builtin_object(&mut space, "J", vec!["F"], vec![]);
    let m_id = MarkusType::define_builtin_object(&mut space, "M", vec![], vec![]);
    let l_id = MarkusType::define_builtin_object(&mut space, "L", vec![], vec![]);

    // ø
    let empty = MarkusType::new_union();
    // x | y
    let mut x_or_y = MarkusType::new_union();
    x_or_y.union_add_member(x_id);
    x_or_y.union_add_member(y_id);
    // y | z
    let mut y_or_z = MarkusType::new_union();
    y_or_z.union_add_member(y_id);
    y_or_z.union_add_member(z_id);
    // x | y | A
    let mut x_or_y_or_a = x_or_y.clone();
    x_or_y_or_a.union_add_member(a_id);
    // A | L
    let mut a_or_l = MarkusType::new_union();
    a_or_l.union_add_member(a_id);
    a_or_l.union_add_member(l_id);
    // L | M
    let mut l_or_m = MarkusType::new_union();
    l_or_m.union_add_member(l_id);
    l_or_m.union_add_member(m_id);
    // B | C
    let mut b_or_c = MarkusType::new_union();
    b_or_c.union_add_member(b_id);
    b_or_c.union_add_member(c_id);
    // C | D
    let mut c_or_d = MarkusType::new_union();
    c_or_d.union_add_member(c_id);
    c_or_d.union_add_member(d_id);
    // x | A
    let mut x_or_a = MarkusType::new_union();
    x_or_a.union_add_member(x_id);
    x_or_a.union_add_member(a_id);
    // x | B
    let mut x_or_b = MarkusType::new_union();
    x_or_b.union_add_member(x_id);
    x_or_b.union_add_member(b_id);
    // x | A | L
    let mut x_or_a_or_l = MarkusType::new_union();
    x_or_a_or_l.union_add_member(x_id);
    x_or_a_or_l.union_add_member(a_id);
    x_or_a_or_l.union_add_member(l_id);
    // A | E
    let mut a_or_e = MarkusType::new_union();
    a_or_e.union_add_member(a_id);
    a_or_e.union_add_member(e_id);
    // A | E | B
    let mut a_or_e_or_b = a_or_e.clone();
    a_or_e_or_b.union_add_member(b_id);
    // J | F
    let mut j_or_f = MarkusType::new_union();
    j_or_f.union_add_member(j_id);
    j_or_f.union_add_member(f_id);
}
