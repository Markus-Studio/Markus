use bit_set;
use daggy;
use petgraph;
use std::cell::RefCell;
use std::collections::HashMap;

const TS_NULL_ID: usize = 0;
const TS_ATOMIC_ID: usize = 1;
const TS_NUMBER_ID: usize = 2;
const TS_STRING_ID: usize = 3;
const TS_USER_ID: usize = 15;

/// Type of the dag used for the base_graph.
pub type TypeDag = daggy::Dag<usize, (), usize>;

#[derive(Debug)]
pub enum TypeSpaceError {
    NameAlreadyInUse,
    UnresolvedName,
    WouldCycle,
    AtomicBase,
    DuplicateField,
}

pub struct TypeSpace {
    name2id: HashMap<String, usize>,
    id2name: HashMap<usize, String>,
    right_resolve_cache: RefCell<HashMap<usize, MarkusType>>,
    left_resolve_cache: RefCell<HashMap<usize, MarkusType>>,
    types: HashMap<usize, TypeInfo>,
    next_id: usize,
    dependencies: TypeDag,
}

pub struct TypeInfo {
    /// Non-recursive base of this type.
    base: MarkusType,
    /// Fields owned by this type.
    owned_fields: HashMap<String, MarkusType>,
}

pub enum Field {
    Owned(MarkusType),
    Derived(MarkusType),
}

#[derive(Clone)]
pub struct MarkusType {
    /// Rank of the type, by default every type is 0-dimensional.
    /// 1-dimensional means an array of type T (T[]), and 2 dimensional means
    /// an array of arrays of T (T[][]).
    pub rank: u8,
    members: bit_set::BitSet,
}

impl TypeSpace {
    /// Returns a new empty TypeSpace.
    pub fn new() -> TypeSpace {
        TypeSpace {
            name2id: HashMap::new(),
            id2name: HashMap::new(),
            right_resolve_cache: RefCell::new(HashMap::new()),
            left_resolve_cache: RefCell::new(HashMap::new()),
            types: HashMap::new(),
            next_id: 0,
            dependencies: daggy::Dag::new(),
        }
    }

    pub fn with_builtin() -> TypeSpace {
        let mut space = TypeSpace::new();
        assert_eq!(space.add_type("null".to_string()).unwrap(), TS_NULL_ID);
        assert_eq!(space.add_type("%atomic".to_string()).unwrap(), TS_ATOMIC_ID);
        // Number
        assert_eq!(space.add_type("%number".to_string()).unwrap(), TS_NUMBER_ID);
        space.connect_atomic(TS_NUMBER_ID, TS_ATOMIC_ID).unwrap();
        // String
        assert_eq!(space.add_type("string".to_string()).unwrap(), TS_STRING_ID);
        space.connect_atomic(TS_STRING_ID, TS_ATOMIC_ID).unwrap();
        // Boolean
        let bid = space.add_type("bool".to_string()).unwrap();
        space.connect_atomic(bid, TS_ATOMIC_ID).unwrap();

        #[inline(always)]
        fn add_number(space: &mut TypeSpace, name: &str) {
            let tid = space.add_type(name.to_string()).unwrap();
            space.connect_atomic(tid, TS_NUMBER_ID).unwrap();
        }

        // Number variants.
        add_number(&mut space, "i8");
        add_number(&mut space, "u8");
        add_number(&mut space, "i16");
        add_number(&mut space, "u16");
        add_number(&mut space, "i32");
        add_number(&mut space, "u32");
        add_number(&mut space, "f32");
        add_number(&mut space, "i64");
        add_number(&mut space, "u64");
        add_number(&mut space, "f64");

        // String
        assert_eq!(space.add_type("user".to_string()).unwrap(), TS_USER_ID);

        space
    }

    /// Add a new type with the given name to the space.
    #[inline]
    pub fn add_type(&mut self, name: String) -> Result<usize, TypeSpaceError> {
        if self.name2id.contains_key(&name) {
            Err(TypeSpaceError::NameAlreadyInUse)
        } else {
            let id = self.next_id;
            self.name2id.insert(name.clone(), id);
            self.id2name.insert(id, name);
            self.types.insert(id, TypeInfo::new());
            assert_eq!(self.dependencies.add_node(id).index(), id);
            self.next_id += 1;
            Ok(id)
        }
    }

    /// Returns the id of the type specified by its name.
    #[inline]
    pub fn get_id(&self, name: &str) -> Result<usize, TypeSpaceError> {
        self.name2id
            .get(name)
            .copied()
            .ok_or(TypeSpaceError::UnresolvedName)
    }

    /// Right-resolve the given name.
    ///
    /// ```txt
    /// type A {}, type B: A {}, type C: B {}
    /// resolve(B) -> B | C
    /// ```
    #[inline(always)]
    pub fn resolve_right(&self, name: &str) -> Result<MarkusType, TypeSpaceError> {
        let id = self.get_id(name)?;
        Ok(self
            .right_resolve_cache
            .borrow_mut()
            .entry(id)
            .or_insert_with(|| {
                let mut result = MarkusType::new();
                result.insert(id);

                for (tid, _) in &self.types {
                    let base = self.resolve_by_id(*tid);
                    if base.contains(id) {
                        result.insert(*tid);
                    }
                }

                result
            })
            .clone())
    }

    /// Left-resolve a type by id.
    ///
    /// ```txt
    /// type A {}, type B: A {}, type C: B {}
    /// resolve(B) -> A | B
    /// ```
    ///
    /// # Panics
    /// If the id is not defined.
    #[inline(always)]
    pub fn resolve_by_id(&self, id: usize) -> MarkusType {
        #[inline(always)]
        fn resolve<'a>(
            cache: &'a mut std::cell::RefMut<HashMap<usize, MarkusType>>,
            types: &HashMap<usize, TypeInfo>,
            id: usize,
        ) -> &'a MarkusType {
            if !cache.contains_key(&id) {
                let mut result = MarkusType::new();
                result.insert(id);
                let info = types.get(&id).unwrap();

                for base in info.base.iter() {
                    let b_rec = resolve(cache, types, base);
                    result.union_with(b_rec);
                }

                cache.insert(id, result);
            }

            cache.get(&id).unwrap()
        }

        let mut cache = self.left_resolve_cache.borrow_mut();
        resolve(&mut cache, &self.types, id).clone()
    }

    /// Left-resolve the given name.
    ///
    /// ```txt
    /// type A {}, type B: A {}, type C: B {}
    /// resolve(B) -> A | B
    /// ```
    ///
    /// This function should be used when you wish to resolve a field type.
    #[inline(always)]
    pub fn resolve(&self, name: &str) -> Result<MarkusType, TypeSpaceError> {
        let id = self.get_id(name)?;
        Ok(self.resolve_by_id(id))
    }

    #[inline(always)]
    fn add_dependency(&mut self, tid: usize, depended: usize) -> Result<(), TypeSpaceError> {
        if tid == depended {
            // Spacial case which `daggy` fails to handle.
            return Err(TypeSpaceError::WouldCycle);
        }
        self.dependencies
            .add_edge(
                daggy::NodeIndex::<usize>::new(tid),
                daggy::NodeIndex::<usize>::new(depended),
                (),
            )
            .map_err(|_| TypeSpaceError::WouldCycle)?;
        Ok(())
    }

    /// Connect two types ignoring AtomicBase error.
    #[inline(always)]
    fn connect_atomic(&mut self, tid: usize, base_id: usize) -> Result<(), TypeSpaceError> {
        self.add_dependency(tid, base_id)?;
        self.left_resolve_cache.borrow_mut().clear();
        self.right_resolve_cache.borrow_mut().clear();
        let type_info = self.types.get_mut(&tid).unwrap();
        type_info.base.insert(base_id);
        Ok(())
    }

    /// Connects two types.
    /// # Panics
    /// If any of the ids are not defined yet.
    #[inline(always)]
    pub fn connect(&mut self, tid: usize, base_id: usize) -> Result<(), TypeSpaceError> {
        let base = self.resolve_by_id(base_id);
        if base.has_atomic() {
            Err(TypeSpaceError::AtomicBase)
        } else {
            self.connect_atomic(tid, base_id)
        }
    }

    /// Add a new field to the current type.
    /// # Panics
    /// If the `tid` can not be resolved.
    #[inline(always)]
    pub fn add_field(
        &mut self,
        tid: usize,
        name: String,
        type_name: &str,
        optional: bool,
    ) -> Result<(), TypeSpaceError> {
        if self.has_field(self.resolve_by_id(tid), &name) {
            Err(TypeSpaceError::DuplicateField)
        } else {
            let type_id = self.get_id(type_name)?;
            let mut field_type = self.resolve_by_id(type_id);

            if optional {
                field_type.insert_null();
            } else {
                self.add_dependency(tid, type_id)?;
            }

            // We have already checked for duplicate fields.
            let info = self.types.get_mut(&tid).unwrap();
            info.add_field(name, field_type).unwrap();

            Ok(())
        }
    }

    /// Returns true if any member in this type contains a field with the given name.
    fn has_field(&self, t: MarkusType, name: &str) -> bool {
        if t.is_never() {
            false
        } else {
            t.iter()
                .any(|id| self.types.get(&id).unwrap().owned_fields.contains_key(name))
        }
    }

    /// Query type of a field on a type.
    pub fn query_field(&self, t: MarkusType, name: &str) -> MarkusType {
        let mut result = MarkusType::new();
        for id in t.iter() {
            let info = self.types.get(&id).unwrap();
            if let Some(field_type) = info.owned_fields.get(name) {
                result.union_with(field_type);
            }
        }
        if !result.is_never() && t.has_null() {
            result.insert_null();
        }
        result.update_rank(t.rank);
        result
    }

    /// Return the topological order of object types.
    pub fn sorted(&self) -> Vec<usize> {
        let graph = self.dependencies.graph();
        let sorted = petgraph::algo::toposort(graph, None).unwrap();
        sorted
            .iter()
            .rev()
            .map(|id| id.index())
            .filter(|id| *id > TS_USER_ID)
            .collect()
    }
}

impl MarkusType {
    /// Returns a new empty 0-dimensional MarkusType.
    pub fn new() -> MarkusType {
        MarkusType {
            rank: 0,
            members: bit_set::BitSet::with_capacity(64),
        }
    }

    /// Returns true if this type is empty.
    #[inline(always)]
    pub fn is_never(&self) -> bool {
        self.members.is_empty()
    }

    /// Returns true if this type contains ATOMIC.
    #[inline(always)]
    pub fn has_atomic(&self) -> bool {
        self.members.contains(TS_ATOMIC_ID)
    }

    /// Returns true if this type contains NUMBER.
    #[inline(always)]
    pub fn has_number(&self) -> bool {
        self.members.contains(TS_NUMBER_ID)
    }

    /// Returns true if this type contains STRING.
    #[inline(always)]
    pub fn has_string(&self) -> bool {
        self.members.contains(TS_STRING_ID)
    }

    /// Returns true if this type contains NULL.
    #[inline(always)]
    pub fn has_null(&self) -> bool {
        self.members.contains(TS_NULL_ID)
    }

    /// Returns true if this type contains the given member.
    #[inline(always)]
    pub fn contains(&self, id: usize) -> bool {
        self.members.contains(id)
    }

    /// Returns an iterator over all of the members in this type.
    #[inline(always)]
    pub fn iter(&self) -> bit_set::Iter<u32> {
        self.members.iter()
    }

    /// Insert the given type id in this type.
    #[inline(always)]
    pub fn insert(&mut self, id: usize) {
        self.members.insert(id);
    }

    /// Unions in-place with the other specified MarkusType.
    #[inline(always)]
    pub fn union_with(&mut self, other: &MarkusType) {
        self.members.union_with(&other.members);
    }

    /// Intersects in-place with the other specified MarkusType.
    #[inline(always)]
    pub fn intersect_with(&mut self, other: &MarkusType) {
        self.members.intersect_with(&other.members);
    }

    /// Updates the rank in-place.
    #[inline(always)]
    pub fn update_rank(&mut self, rank: u8) {
        self.rank = rank;
    }

    /// Inserts `null` in this type set.
    pub fn insert_null(&mut self) {
        self.members.insert(TS_NULL_ID);
    }
}

impl TypeInfo {
    pub fn new() -> TypeInfo {
        TypeInfo {
            base: MarkusType::new(),
            owned_fields: HashMap::new(),
        }
    }

    /// Add a new field to this type.
    #[inline]
    pub fn add_field(
        &mut self,
        name: String,
        field_type: MarkusType,
    ) -> Result<(), TypeSpaceError> {
        if self.owned_fields.contains_key(&name) {
            Err(TypeSpaceError::DuplicateField)
        } else {
            self.owned_fields.insert(name, field_type);
            Ok(())
        }
    }
}
