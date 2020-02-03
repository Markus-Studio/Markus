#![allow(dead_code)]
use crate::parser::ast::TypeDeclarationNode;
use std::collections::{HashMap, HashSet, VecDeque};
use std::rc::Rc;

type TypeId = u32;

#[derive(Clone, Debug)]
pub enum MarkusTypeInfo {
    Atomic,
    Never,
    Union {
        members: Vec<TypeId>,
    },
    BuiltInObject {
        parents: Vec<TypeId>,
        fields: HashMap<String, TypeId>,
    },
    Object {
        ast: Rc<TypeDeclarationNode>,
    },
}

#[derive(Clone, Debug)]
pub struct MarkusType {
    pub id: TypeId,
    /// This value indicates dimension of the actual type, a type such as
    /// `x` where x is an atomic is considered a 0-dimensional type while
    /// `x[]` and `x[][]` are true and 2-dimensional accordingly.
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
                (String::from("lat"), f32_id),
                (String::from("long"), f32_id),
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
        // Two types must be of the same order in order to be compared.
        if lhs.dimension != rhs.dimension {
            return false;
        }

        // `nil` is not `nil` - if that makes sense.
        if lhs.is_nil() || rhs.is_nil() {
            return false;
        }

        if lhs.id > 0 && lhs.id == rhs.id {
            return true;
        }

        match (&lhs.type_info, &rhs.type_info) {
            (MarkusTypeInfo::Atomic, MarkusTypeInfo::Atomic) => {
                // Two atomic types are considered to be same if and only if
                // they share the same id.
                lhs.id == rhs.id
            }
            (MarkusTypeInfo::Atomic, MarkusTypeInfo::Union { ref members }) => {
                // `x is T: {A, B, ...}` holds true for all x-es that are in the T.
                members.contains(&lhs.id)
            }
            (MarkusTypeInfo::Atomic, _) => {
                // An atomic type is only assignable to another atomic.
                false
            }
            (MarkusTypeInfo::Union { ref members }, MarkusTypeInfo::Atomic) => {
                // `T: {A, B, ...} is x` if and only if T = {x}
                members.len() == 1 && members[0] == rhs.id
            }
            (MarkusTypeInfo::Union { ref members }, MarkusTypeInfo::Object { .. })
            | (MarkusTypeInfo::Union { ref members }, MarkusTypeInfo::BuiltInObject { .. })
            | (MarkusTypeInfo::Union { ref members }, MarkusTypeInfo::Union { .. }) => {
                if members.len() == 0 {
                    false
                } else {
                    for &type_id in members {
                        let member = self.resolve_type_by_id(type_id).unwrap();
                        if !self.is(member, rhs) {
                            return false;
                        }
                    }
                    true
                }
            }
            (MarkusTypeInfo::Object { .. }, MarkusTypeInfo::Object { .. })
            | (MarkusTypeInfo::Object { .. }, MarkusTypeInfo::BuiltInObject { .. })
            | (MarkusTypeInfo::BuiltInObject { .. }, MarkusTypeInfo::Object { .. })
            | (MarkusTypeInfo::BuiltInObject { .. }, MarkusTypeInfo::BuiltInObject { .. }) => {
                // `o1: {all_parents} is o2` is true for all such that o2 is a member of all_parents.
                // (we have already handled the o1 == o2 at above)
                for parent in lhs.object_get_parents_recursive(self) {
                    if parent == rhs.id {
                        return true;
                    }
                }
                false
            }
            (MarkusTypeInfo::Object { .. }, MarkusTypeInfo::Union { ref members })
            | (MarkusTypeInfo::BuiltInObject { .. }, MarkusTypeInfo::Union { ref members }) => {
                for &type_id in members {
                    let member = self.resolve_type_by_id(type_id).unwrap();
                    if self.is(lhs, member) {
                        return true;
                    }
                }
                false
            }
            (MarkusTypeInfo::Object { .. }, MarkusTypeInfo::Atomic)
            | (MarkusTypeInfo::BuiltInObject { .. }, MarkusTypeInfo::Atomic) => false,
            (MarkusTypeInfo::Never, _) | (_, MarkusTypeInfo::Never) => false,
        }
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
        fields: Vec<(String, TypeId)>,
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
                    fields: fields.into_iter().collect(),
                },
            },
        );
        id
    }

    pub fn define_object(space: &mut TypeSpace, node: Rc<TypeDeclarationNode>) {}

    /// Creates a new empty union.
    pub fn new_union() -> MarkusType {
        MarkusType {
            id: 0,
            dimension: 0,
            type_info: MarkusTypeInfo::Union { members: vec![] },
        }
    }

    #[inline]
    pub fn is_atomic(&self) -> bool {
        match self.type_info {
            MarkusTypeInfo::Atomic => true,
            _ => false,
        }
    }

    #[inline]
    pub fn is_never(&self) -> bool {
        match self.type_info {
            MarkusTypeInfo::Never => true,
            _ => false,
        }
    }

    #[inline]
    pub fn is_union(&self) -> bool {
        match self.type_info {
            MarkusTypeInfo::Union { .. } => true,
            _ => false,
        }
    }

    #[inline]
    pub fn is_object(&self) -> bool {
        match self.type_info {
            MarkusTypeInfo::Object { .. } | MarkusTypeInfo::BuiltInObject { .. } => true,
            _ => false,
        }
    }

    /// Returns true if this type is evaluated to be `nil`.
    #[inline]
    pub fn is_nil(&self) -> bool {
        match self.type_info {
            MarkusTypeInfo::Never => true,
            MarkusTypeInfo::Union { ref members } => members.len() == 0,
            _ => false,
        }
    }

    /// Add a member to a union type.
    pub fn union_add_member(&mut self, id: TypeId) {
        if let MarkusTypeInfo::Union { ref mut members } = self.type_info {
            members.push(id);
        } else {
            panic!("union_add_member is only for union types.");
        }
    }

    #[inline]
    pub fn object_get_parents(&self, space: &TypeSpace) -> Vec<TypeId> {
        match self.type_info {
            MarkusTypeInfo::Object { ref ast } => {
                let mut result: Vec<TypeId> = Vec::with_capacity(ast.bases.len());
                for base in &ast.bases {
                    if let Some(&id) = space.resolve_type_id(&base.value) {
                        result.push(id);
                    }
                }
                result
            }
            MarkusTypeInfo::BuiltInObject { ref parents, .. } => parents.clone(),
            _ => panic!("object_get_parents is only for object types."),
        }
    }

    /// Returns a set containing all of the parents in the current type.
    #[inline]
    pub fn object_get_parents_recursive(&self, space: &TypeSpace) -> HashSet<TypeId> {
        let mut seen: HashSet<TypeId> = HashSet::new();
        let mut to_see: VecDeque<TypeId> = VecDeque::from(self.object_get_parents(space));

        while let Some(current_id) = to_see.pop_front() {
            if seen.insert(current_id) {
                let current_type = space.resolve_type_by_id(current_id).unwrap();
                let current_parents = current_type.object_get_parents_recursive(space);
                let additional = current_parents.len();
                if additional > 0 {
                    seen.reserve(additional);
                    to_see.reserve(additional);
                }
                for new_id in current_parents {
                    seen.insert(new_id);
                    to_see.push_back(new_id);
                }
            }
        }

        seen
    }

    /// Returns whatever the current object owns a field with the given name.
    #[inline]
    pub fn object_owns(&self, name: &str) -> bool {
        match self.type_info {
            MarkusTypeInfo::BuiltInObject { ref fields, .. } => fields.get(name) != None,
            MarkusTypeInfo::Object { ref ast } => {
                for field in &ast.fields {
                    match &field.name {
                        Some(identifier) if identifier.value == name => return true,
                        _ => {}
                    }
                }
                false
            }
            _ => panic!("object_owns is only for object types."),
        }
    }
}

#[test]
fn is() {
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

    let x = space.resolve_type("x").unwrap();
    let y = space.resolve_type("y").unwrap();
    let z = space.resolve_type("z").unwrap();

    let a = space.resolve_type_by_id(a_id).unwrap();
    let b = space.resolve_type_by_id(b_id).unwrap();
    let c = space.resolve_type_by_id(c_id).unwrap();
    let d = space.resolve_type_by_id(d_id).unwrap();
    let e = space.resolve_type_by_id(e_id).unwrap();
    let f = space.resolve_type_by_id(f_id).unwrap();
    let l = space.resolve_type_by_id(l_id).unwrap();
    let j = space.resolve_type_by_id(j_id).unwrap();

    assert_eq!(space.is(x, x), true);
    assert_eq!(space.is(x, y), false);
    assert_eq!(space.is(x, &x_or_y), true);
    assert_eq!(space.is(x, &y_or_z), false);
    assert_eq!(space.is(x, &x_or_y_or_a), true);
    assert_eq!(space.is(x, &empty), false);

    assert_eq!(space.is(a, a), true);
    assert_eq!(space.is(a, b), true);
    assert_eq!(space.is(b, a), false);
    assert_eq!(space.is(b, c), false);
    assert_eq!(space.is(a, d), true);
    assert_eq!(space.is(a, l), false);
    assert_eq!(space.is(a, &a_or_l), true);
    assert_eq!(space.is(a, &x_or_a), true);
    assert_eq!(space.is(a, &x_or_a_or_l), true);
    assert_eq!(space.is(a, &l_or_m), false);
    assert_eq!(space.is(a, &b_or_c), true);
    assert_eq!(space.is(a, &c_or_d), true);
    assert_eq!(space.is(a, &x_or_y_or_a), true);
    assert_eq!(space.is(a, &empty), false);
    assert_eq!(space.is(j, d), true);

    assert_eq!(space.is(y, &x_or_y), true);
    assert_eq!(space.is(y, &empty), false);
    assert_eq!(space.is(y, &x_or_y_or_a), true);
    assert_eq!(space.is(y, x), false);
    assert_eq!(space.is(y, z), false);

    assert_eq!(space.is(a, &x_or_a), true);
    assert_eq!(space.is(a, x), false);
    assert_eq!(space.is(a, &x_or_b), true);
    assert_eq!(space.is(a, &x_or_a_or_l), true);

    assert_eq!(space.is(e, c), true);
    assert_eq!(space.is(f, e), true);
    assert_eq!(space.is(l, c), false);
    assert_eq!(space.is(b, c), false);
    assert_eq!(space.is(b, &b_or_c), true);
    assert_eq!(space.is(c, a), false);
}
