use super::diagnostics::*;
use bit_set::BitSet;
use daggy;
use daggy::Walker;
use petgraph;
use std::collections::HashMap;

const NULL_ID: usize = 0;
const ATOMIC_ID: usize = 1;
const NUMBER_ID: usize = 2;
const SIGNED_ID: usize = 3;
const UNSIGNED_ID: usize = 4;
const FLOAT_ID: usize = 5;
const USER_ID: usize = 18;

/// Type of the dag used for the base_graph.
pub type TypeDag = daggy::Dag<usize, (), usize>;

/// The TypeSpaceGraph is the core part of the TypeSpace, each TypeSpace owns
/// a TypeSpaceGraph which is the ds to store name of each type (either user
/// defined or builtin)
pub struct TypeSpaceGraph {
    name2id: HashMap<String, usize>,
    id2name: HashMap<usize, String>,
    next_id: usize,
    base_graph: TypeDag,
}

pub struct TypeSpace {
    graph: TypeSpaceGraph,
    dependency_graph: TypeDag,
    owned_fields: HashMap<usize, HashMap<String, TypeRef>>,
}

#[derive(Debug)]
pub struct TypeRef(BitSet);

impl TypeSpaceGraph {
    pub fn new() -> TypeSpaceGraph {
        TypeSpaceGraph {
            name2id: HashMap::new(),
            id2name: HashMap::new(),
            next_id: 0,
            base_graph: daggy::Dag::new(),
        }
    }

    pub fn init_builtin(&mut self) -> Result<(), Diagnostic> {
        assert_eq!(self.next_id, 0);
        assert_eq!(self.add_type("%null".to_string())?, NULL_ID);
        assert_eq!(self.add_type("%atomic".to_string())?, ATOMIC_ID);

        // Create number categories.
        assert_eq!(self.add_atomic("%number".to_string())?, NUMBER_ID);
        assert_eq!(self.add_type("%signed".to_string())?, SIGNED_ID);
        assert_eq!(self.add_type("%unsigned".to_string())?, UNSIGNED_ID);
        assert_eq!(self.add_type("%float".to_string())?, FLOAT_ID);
        self.connect_atomic("%number", "%signed")?;
        self.connect_atomic("%number", "%unsigned")?;
        self.connect_atomic("%signed", "%float")?;

        // Signed numbers.
        self.add_type("i8".to_string())?;
        self.add_type("i16".to_string())?;
        self.add_type("i32".to_string())?;
        self.add_type("i64".to_string())?;
        self.connect_atomic("%signed", "i8")?;
        self.connect_atomic("%signed", "i16")?;
        self.connect_atomic("%signed", "i32")?;
        self.connect_atomic("%signed", "i64")?;

        // Unsigned numbers.
        self.add_type("u8".to_string())?;
        self.add_type("u16".to_string())?;
        self.add_type("u32".to_string())?;
        self.add_type("u64".to_string())?;
        self.connect_atomic("%unsigned", "u8")?;
        self.connect_atomic("%unsigned", "u16")?;
        self.connect_atomic("%unsigned", "u32")?;
        self.connect_atomic("%unsigned", "u64")?;

        // Float numbers.
        self.add_type("f32".to_string())?;
        self.add_type("f64".to_string())?;
        self.connect_atomic("%float", "f32")?;
        self.connect_atomic("%float", "f64")?;

        // Other atomic types.
        self.add_atomic("str".to_string())?;
        self.add_atomic("bool".to_string())?;

        // Special user object.
        assert_eq!(self.add_type("user".to_string())?, USER_ID);

        Ok(())
    }

    #[inline]
    fn add_atomic(&mut self, name: String) -> Result<usize, Diagnostic> {
        let id = self.add_type(name.clone())?;
        self.connect_atomic("%atomic", &name)?;
        Ok(id)
    }

    pub fn add_type(&mut self, name: String) -> Result<usize, Diagnostic> {
        if self.name2id.contains_key(&name) {
            Err(Diagnostic::new(DiagnosticKind::NameAlreadyInUse, None))
        } else {
            let id = self.next_id;
            self.name2id.insert(name.clone(), id);
            self.id2name.insert(id, name);
            assert_eq!(self.base_graph.add_node(id).index(), id);
            self.next_id += 1;
            Ok(id)
        }
    }

    #[inline]
    pub fn connect_atomic(&mut self, base: &str, child: &str) -> Result<(), Diagnostic> {
        if base == child {
            return Err(Diagnostic::new(DiagnosticKind::CircularBaseGraph, None));
        }

        let base = *self
            .name2id
            .get(base)
            .ok_or(Diagnostic::new(DiagnosticKind::CannotResolveName, None))?;
        let child = *self
            .name2id
            .get(child)
            .ok_or(Diagnostic::new(DiagnosticKind::CannotResolveName, None))?;
        self.base_graph
            .add_edge(
                daggy::NodeIndex::<usize>::new(child),
                daggy::NodeIndex::<usize>::new(base),
                (),
            )
            .map_err(|_| Diagnostic::new(DiagnosticKind::CircularBaseGraph, None))?;
        Ok(())
    }

    pub fn connect(&mut self, base: &str, child: &str) -> Result<(), Diagnostic> {
        if self.is_atomic(base)? {
            Err(Diagnostic::new(DiagnosticKind::AtomicTypeUsedAsBase, None))
        } else {
            self.connect_atomic(base, child)
        }
    }

    pub fn sorted(&self) -> Vec<usize> {
        let graph = self.base_graph.graph();
        let sorted = petgraph::algo::toposort(graph, None).unwrap();
        sorted
            .iter()
            .rev()
            .map(|id| id.index())
            .filter(|id| *id > USER_ID)
            .collect()
    }

    fn is_atomic(&self, child: &str) -> Result<bool, Diagnostic> {
        let child = *self
            .name2id
            .get(child)
            .ok_or(Diagnostic::new(DiagnosticKind::CannotResolveName, None))?;
        let child = daggy::NodeIndex::<usize>::new(child);
        let base = daggy::NodeIndex::<usize>::new(ATOMIC_ID);
        let graph = self.base_graph.graph();
        Ok(petgraph::algo::has_path_connecting(
            graph, child, base, None,
        ))
    }

    pub fn resolve_by_id(&self, id: usize) -> TypeRef {
        fn visit(type_ref: &mut TypeRef, g: &TypeDag, index: usize) {
            type_ref.insert(index);
            let parent = daggy::NodeIndex::<usize>::new(index);
            let walker = g.children(parent);
            for child in walker.iter(g) {
                let index = child.1.index();
                visit(type_ref, g, index);
            }
        }

        let mut type_ref = TypeRef::new();
        visit(&mut type_ref, &self.base_graph, id);
        type_ref
    }

    pub fn resolve(&self, name: &str) -> Result<TypeRef, Diagnostic> {
        let index = *self
            .name2id
            .get(name)
            .ok_or(Diagnostic::new(DiagnosticKind::CannotResolveName, None))?;

        Ok(self.resolve_by_id(index))
    }
}

impl TypeSpace {
    pub fn new(graph: TypeSpaceGraph) -> TypeSpace {
        let dependency_graph = graph.base_graph.clone();
        TypeSpace {
            graph,
            dependency_graph,
            owned_fields: HashMap::new(),
        }
    }

    pub fn empty() -> TypeSpace {
        TypeSpace {
            graph: TypeSpaceGraph::new(),
            dependency_graph: daggy::Dag::new(),
            owned_fields: HashMap::new(),
        }
    }

    pub fn update_graph(&mut self, graph: TypeSpaceGraph) {
        assert_eq!(self.owned_fields.len(), 0);
        self.dependency_graph = graph.base_graph.clone();
        self.graph = graph;
    }

    pub fn contains_field(&self, dt: &TypeRef, field_name: &str) -> bool {
        if dt.is_atomic() {
            false
        } else {
            dt.iter().all(|id| match self.owned_fields.get(&id) {
                Some(map) => map.contains_key(field_name),
                None => false,
            })
        }
    }

    pub fn resolve_field(&self, dt: &TypeRef, field_name: &str) -> TypeRef {
        if dt.is_atomic() {
            TypeRef::new()
        } else {
            let mut result = TypeRef::new();
            for x in dt.iter().map(|id| {
                self.owned_fields
                    .get(&id)
                    .map(|map| map.get(field_name))
                    .unwrap_or(None)
            }) {
                if let Some(x) = x {
                    result.union_with(x);
                } else {
                    return TypeRef::new();
                }
            }
            result
        }
    }

    pub fn add_field(
        &mut self,
        owner: usize,
        name: String,
        type_name: &str,
        optional: bool,
    ) -> Result<(), Diagnostic> {
        let has_field = {
            if let Some(m) = self.owned_fields.get(&owner) {
                m.contains_key(&name)
            } else {
                false
            }
        };

        let mut field_type = self.resolve(type_name)?;
        if optional {
            field_type.insert_null();
        }

        if has_field {
            Err(Diagnostic::new(DiagnosticKind::FieldNameAlreadyInUse, None))
        } else if self.contains_field(&self.graph.resolve_by_id(owner), &name) {
            Err(Diagnostic::new(
                DiagnosticKind::FieldNameAppearsInParent,
                None,
            ))
        } else {
            if !field_type.is_null() && !field_type.is_never() {
                let a = daggy::NodeIndex::<usize>::new(owner);
                let b = daggy::NodeIndex::<usize>::new(*self.graph.name2id.get(type_name).unwrap());
                self.dependency_graph
                    .add_edge(a, b, ())
                    .map_err(|_| Diagnostic::new(DiagnosticKind::RequiredCircularField, None))?;
            }

            let map = self
                .owned_fields
                .entry(owner)
                .or_insert_with(|| HashMap::new());
            map.insert(name, field_type);
            Ok(())
        }
    }

    #[inline(always)]
    pub fn resolve(&self, name: &str) -> Result<TypeRef, Diagnostic> {
        self.graph.resolve(name)
    }
}

impl TypeRef {
    pub fn new() -> TypeRef {
        TypeRef(BitSet::with_capacity(512))
    }

    pub fn from_set(set: BitSet) -> TypeRef {
        TypeRef(set)
    }

    #[inline(always)]
    pub fn insert(&mut self, index: usize) {
        self.0.insert(index);
    }

    #[inline(always)]
    pub fn insert_null(&mut self) {
        self.0.insert(NULL_ID);
    }

    #[inline(always)]
    pub fn union_with(&mut self, other: &TypeRef) {
        self.0.union_with(&other.0);
    }

    #[inline(always)]
    pub fn intersect_with(&mut self, other: &TypeRef) {
        self.0.intersect_with(&other.0);
    }

    #[inline(always)]
    pub fn iter(&self) -> bit_set::Iter<u32> {
        self.0.iter()
    }

    #[inline(always)]
    pub fn is_never(&self) -> bool {
        self.0.is_empty()
    }

    #[inline(always)]
    pub fn is_null(&self) -> bool {
        self.0.contains(NULL_ID)
    }

    #[inline(always)]
    pub fn is_atomic(&self) -> bool {
        self.0.contains(ATOMIC_ID)
    }

    #[inline(always)]
    pub fn is_number(&self) -> bool {
        self.0.contains(NUMBER_ID)
    }

    #[inline(always)]
    pub fn is_signed(&self) -> bool {
        self.0.contains(SIGNED_ID)
    }

    #[inline(always)]
    pub fn is_unsigned(&self) -> bool {
        self.0.contains(UNSIGNED_ID)
    }

    #[inline(always)]
    pub fn is_float(&self) -> bool {
        self.0.contains(FLOAT_ID)
    }

    #[inline(always)]
    pub fn is_user(&self) -> bool {
        self.0.contains(USER_ID)
    }

    #[inline(always)]
    pub fn is(&self, other: &TypeRef) -> bool {
        other.0.is_subset(&self.0)
    }
}

#[test]
fn base_graph() {
    let mut g = TypeSpaceGraph::new();
    g.init_builtin().unwrap();

    assert!(g.resolve("%number").unwrap().is_number());

    let i32_t = g.resolve("i32").unwrap();
    assert!(i32_t.is_atomic());
    assert!(i32_t.is_number());
    assert!(i32_t.is_signed());
    assert!(!i32_t.is_unsigned());
    assert!(!i32_t.is_float());

    let u32_t = g.resolve("u32").unwrap();
    assert!(u32_t.is_atomic());
    assert!(u32_t.is_number());
    assert!(!u32_t.is_signed());
    assert!(u32_t.is_unsigned());
    assert!(!u32_t.is_float());

    let f32_t = g.resolve("f32").unwrap();
    assert!(f32_t.is_atomic());
    assert!(f32_t.is_number());
    assert!(f32_t.is_signed());
    assert!(!i32_t.is_unsigned());
    assert!(f32_t.is_float());

    let number_t = g.resolve("%number").unwrap();
    assert!(i32_t.is(&number_t));
    assert!(u32_t.is(&number_t));
    assert!(f32_t.is(&number_t));

    let a_id = g.add_type("A".to_string()).unwrap();
    let b_id = g.add_type("B".to_string()).unwrap();
    let c_id = g.add_type("C".to_string()).unwrap();

    g.connect("A", "C").unwrap();
    g.connect("B", "C").unwrap();

    assert!(g
        .resolve("C")
        .unwrap()
        .iter()
        .eq(vec![a_id, b_id, c_id].into_iter()));
}
