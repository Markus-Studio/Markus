use bit_set::BitSet;
use std::collections::HashMap;

pub struct TypeSpace {
    name2id: HashMap<String, usize>,
    id2name: HashMap<usize, String>,
    fields: HashMap<usize, HashMap<String, TypeRef>>,
    resolved: HashMap<usize, TypeRef>,
}

#[derive(Debug, PartialEq, Clone)]
pub struct TypeRef {
    rank: u8,
    members: BitSet,
}

impl TypeSpace {
    pub fn new() -> TypeSpace {
        TypeSpace {
            name2id: HashMap::new(),
            id2name: HashMap::new(),
            fields: HashMap::new(),
            resolved: HashMap::new(),
        }
    }

    pub fn add_type(&mut self, name: String, id: usize, resolved: BitSet) {
        self.name2id.insert(name.clone(), id);
        self.id2name.insert(id, name);
        self.fields.insert(id, HashMap::new());
        self.resolved.insert(id, TypeRef::with_members(resolved));
    }

    pub fn add_field(&mut self, field_id: &usize, name: String, field_type: TypeRef) {
        let fields = self.fields.get_mut(field_id).unwrap();
        fields.insert(name, field_type);
    }

    pub fn resolve(&self, name: &str) -> TypeRef {
        let id = self.name2id.get(name).expect("Failed to resolve the type.");
        self.resolved.get(&id).unwrap().clone()
    }
}

impl TypeRef {
    pub fn new() -> TypeRef {
        TypeRef {
            rank: 0,
            members: BitSet::with_capacity(128),
        }
    }

    pub fn with_members(members: BitSet) -> TypeRef {
        TypeRef { rank: 0, members }
    }

    #[inline(always)]
    pub fn with_rank(&mut self, rank: u8) {
        self.rank = rank;
    }

    #[inline(always)]
    pub fn union_with(&mut self, other: &TypeRef) {
        self.members.union_with(&other.members);
    }

    #[inline(always)]
    pub fn intersect_with(&mut self, other: &TypeRef) {
        self.members.intersect_with(&other.members);
    }

    #[inline(always)]
    pub fn is_superset(&self, other: &TypeRef) -> bool {
        self.members.is_superset(&other.members)
    }

    #[inline(always)]
    pub fn is_subset(&self, other: &TypeRef) -> bool {
        self.members.is_subset(&other.members)
    }

    #[inline(always)]
    pub fn is_never(&self) -> bool {
        self.members.is_empty()
    }

    #[inline(always)]
    pub fn rank(&self) -> u8 {
        self.rank
    }

    #[inline(always)]
    pub fn iter(&self) -> bit_set::Iter<u32> {
        self.members.iter()
    }
}
