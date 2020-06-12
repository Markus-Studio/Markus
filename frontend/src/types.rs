use super::diagnostics::*;
use bitflags;
use common::bimap::BiMap;
use std::collections::{HashMap, HashSet};

bitflags! {
  pub struct PrimitiveType: u32 {
      const NEVER   = 0b_0000_0000_0000_0000;
      const NUMBER  = 0b_0000_0000_0000_0001;
      const BOOLEAN = 0b_0000_0000_0000_0010;
      const STRING  = 0b_0000_0000_0000_0100;
      const I08     = 0b_0000_0000_0001_0000 | Self::NUMBER.bits;
      const U08     = 0b_0000_0000_0010_0000 | Self::NUMBER.bits;
      const I16     = 0b_0000_0000_0100_0000 | Self::NUMBER.bits;
      const U16     = 0b_0000_0000_1000_0000 | Self::NUMBER.bits;
      const I32     = 0b_0000_0001_0000_0000 | Self::NUMBER.bits;
      const U32     = 0b_0000_0010_0000_0000 | Self::NUMBER.bits;
      const F32     = 0b_0000_0100_0000_0000 | Self::NUMBER.bits;
      const I64     = 0b_0000_1000_0000_0000 | Self::NUMBER.bits;
      const U64     = 0b_0001_0000_0000_0000 | Self::NUMBER.bits;
      const F64     = 0b_0010_0000_0000_0000 | Self::NUMBER.bits;
      const TRUE    = 0b_0100_0000_0000_0000 | Self::BOOLEAN.bits;
      const FALSE   = 0b_1000_0000_0000_0000 | Self::BOOLEAN.bits;
  }
}

/// The typespace contains all of the types in the program it's the unit
/// responsible for answering type queries.
#[derive(Debug, Clone)]
pub struct Space<'a> {
    /// Maps id of each object to its information.
    objects: HashMap<usize, ObjectInfo<'a>>,
    /// A bi-directional map that maps name of each type to its id and vice versa.
    object_names: BiMap<String, usize>,
    // The type id counter.
    next_id: usize,
}

/// A reference to a single type.
#[derive(Debug, Clone)]
pub struct MarkusType<'a> {
    pub rank: usize,
    space: &'a Space<'a>,
    primitive: PrimitiveType,
    objects: HashSet<usize>,
}

/// Information for an object type, such as its fields and list of its parents.
#[derive(Debug, Clone)]
pub struct ObjectInfo<'a> {
    fields: HashMap<String, FieldInfo<'a>>,
    bases: HashSet<usize>,
}

#[derive(Debug, Clone)]
pub struct FieldInfo<'a> {
    pub optional: bool,
    pub dt: MarkusType<'a>,
}

impl<'a> Space<'a> {
    pub fn new() -> Space<'a> {
        Space {
            objects: HashMap::new(),
            object_names: BiMap::new(),
            next_id: 0,
        }
    }

    pub fn add_object<'b: 'a>(
        &mut self,
        name: String,
        info: ObjectInfo<'b>,
    ) -> Result<usize, Diagnostic> {
        if self.resolve(&name).is_ok() {
            return Err(Diagnostic::new(DiagnosticKind::NameAlreadyInUse, None));
        }

        let id = self.next_id;
        self.next_id += 1;

        self.object_names.insert(name, id);
        self.objects.insert(id, info);

        Ok(id)
    }

    /// Resolves an object id by its name.
    #[inline]
    pub fn get_object_id(&self, name: &String) -> Option<usize> {
        self.object_names.get_by_left(name).copied()
    }

    /// Resolves an object by its id.
    #[inline]
    pub fn get_object_by_id(&self, id: &usize) -> Option<&'a ObjectInfo> {
        self.objects.get(id)
    }

    /// Returns a mutable reference to an object info by its id.
    #[inline]
    pub fn get_object_by_id_mut<'b>(&'b mut self, id: &usize) -> Option<&mut ObjectInfo<'a>>
    where
        'a: 'b,
    {
        self.objects.get_mut(id)
    }

    /// Returns an iterator visiting all (object_id, info) pairs with mutable reference
    /// to `info`.
    #[inline]
    pub fn objects_mut(
        &mut self,
    ) -> std::collections::hash_map::IterMut<'_, usize, ObjectInfo<'a>> {
        self.objects.iter_mut()
    }

    #[inline]
    pub fn object_ids(&self) -> std::ops::Range<usize> {
        0..self.next_id
    }

    /// Returns a reference to an object info by its name.
    #[inline]
    pub fn get_object_by_name(&self, name: &String) -> Option<&'a ObjectInfo> {
        match self.object_names.get_by_left(name) {
            Some(id) => self.objects.get(id),
            None => None,
        }
    }

    /// Returns a mutable reference to an object info by its name.
    #[inline]
    pub fn get_object_by_name_mut<'b>(&'b mut self, name: &String) -> Option<&mut ObjectInfo<'a>>
    where
        'a: 'b,
    {
        match self.object_names.get_by_left(name) {
            Some(id) => self.objects.get_mut(id),
            None => None,
        }
    }

    /// Resolve a type by its name.
    pub fn resolve(&'a self, name: &String) -> Result<MarkusType<'a>, Diagnostic> {
        match name as &str {
            "bool" => Ok(MarkusType::new(&self, 0, PrimitiveType::BOOLEAN, 0..0)),
            "string" => Ok(MarkusType::new(&self, 0, PrimitiveType::STRING, 0..0)),
            "%num" => Ok(MarkusType::new(&self, 0, PrimitiveType::NUMBER, 0..0)),
            "i8" => Ok(MarkusType::new(&self, 0, PrimitiveType::I08, 0..0)),
            "u8" => Ok(MarkusType::new(&self, 0, PrimitiveType::U08, 0..0)),
            "i16" => Ok(MarkusType::new(&self, 0, PrimitiveType::I16, 0..0)),
            "u16" => Ok(MarkusType::new(&self, 0, PrimitiveType::U16, 0..0)),
            "i32" => Ok(MarkusType::new(&self, 0, PrimitiveType::I32, 0..0)),
            "u32" => Ok(MarkusType::new(&self, 0, PrimitiveType::U32, 0..0)),
            "f32" => Ok(MarkusType::new(&self, 0, PrimitiveType::F32, 0..0)),
            "i64" => Ok(MarkusType::new(&self, 0, PrimitiveType::I64, 0..0)),
            "u64" => Ok(MarkusType::new(&self, 0, PrimitiveType::U64, 0..0)),
            "f64" => Ok(MarkusType::new(&self, 0, PrimitiveType::F64, 0..0)),
            "true" => Ok(MarkusType::new(&self, 0, PrimitiveType::TRUE, 0..0)),
            "false" => Ok(MarkusType::new(&self, 0, PrimitiveType::FALSE, 0..0)),
            _ => {
                if let Some(&id) = self.object_names.get_by_left(name) {
                    Ok(MarkusType::new(
                        &self,
                        0,
                        PrimitiveType::NEVER,
                        id..(id + 1),
                    ))
                } else {
                    Err(Diagnostic::new(DiagnosticKind::CannotResolveName, None))
                }
            }
        }
    }

    pub fn next_id(&self) -> usize {
        self.next_id
    }
}

impl<'a> ObjectInfo<'a> {
    pub fn new() -> ObjectInfo<'a> {
        ObjectInfo {
            fields: HashMap::new(),
            bases: HashSet::new(),
        }
    }

    pub fn get_bases(&'a self) -> &'a HashSet<usize> {
        &self.bases
    }

    pub fn add_base(&mut self, id: usize) {
        self.bases.insert(id);
    }

    pub fn get_field(&self, name: &String) -> Option<&'a FieldInfo> {
        self.fields.get(name)
    }

    pub fn add_field(&mut self, name: String, info: FieldInfo<'a>) -> Result<(), Diagnostic> {
        if self.fields.contains_key(&name) {
            return Err(Diagnostic::new(DiagnosticKind::FieldNameAlreadyInUse, None));
        }
        self.fields.insert(name, info);
        Ok(())
    }
}

impl<'a> FieldInfo<'a> {
    pub fn new(optional: bool, dt: MarkusType<'a>) -> FieldInfo<'a> {
        FieldInfo { optional, dt }
    }
}

impl<'a> MarkusType<'a> {
    pub fn new<T: IntoIterator<Item = usize>>(
        space: &'a Space,
        rank: usize,
        primitive: PrimitiveType,
        objects: T,
    ) -> MarkusType<'a> {
        MarkusType {
            space,
            rank,
            primitive,
            objects: objects.into_iter().collect(),
        }
    }

    pub fn empty(space: &'a Space, rank: usize) -> MarkusType<'a> {
        MarkusType {
            space,
            rank,
            primitive: PrimitiveType::NEVER,
            objects: HashSet::new(),
        }
    }

    /// Changes the rank of this type.
    pub fn with_rank(&self, new_rank: usize) -> MarkusType<'a> {
        MarkusType::new(self.space, new_rank, self.primitive, self.objects.clone())
    }

    /// Returns the current type without primitives.
    pub fn obj(&self) -> MarkusType<'a> {
        MarkusType::new(
            self.space,
            self.rank,
            PrimitiveType::NEVER,
            self.objects.clone(),
        )
    }

    /// Returns the current type without objects.
    pub fn prim(&self) -> MarkusType<'a> {
        MarkusType::new(self.space, self.rank, self.primitive, 0..0)
    }

    /// Expands the current types, traverse the base graph of each object type
    /// in this type recursively and inserts them into the `objects` set.
    pub fn expand(&self) -> MarkusType<'a> {
        let mut objects = HashSet::<usize>::with_capacity(self.objects.len());
        let mut to_visit: Vec<usize> = self.objects.iter().copied().collect();

        while let Some(node_id) = to_visit.pop() {
            if objects.contains(&node_id) {
                continue;
            }

            let node = self.space.get_object_by_id(&node_id).unwrap();
            for base_id in node.get_bases() {
                to_visit.push(*base_id);
            }

            objects.insert(node_id);
        }

        MarkusType::new(self.space, self.rank, self.primitive, objects)
    }

    pub fn resolve_field(&self, name: &String) -> Result<MarkusType, Diagnostic> {
        if !self.primitive.is_empty() || self.objects.is_empty() {
            return Err(Diagnostic::new(DiagnosticKind::FieldNotFound, None));
        }

        let fields = self.objects.iter().map(|id| {
            let node = self.space.get_object_by_id(id).unwrap();
            node.get_field(name).map(|info| info.dt.clone())
        });

        if fields.clone().any(|x| x.is_none()) {
            return Err(Diagnostic::new(DiagnosticKind::FieldNotFound, None));
        }

        Ok(fields
            .map(|x| x.unwrap())
            .fold(MarkusType::empty(self.space, 0), |a, b| (a | b).unwrap())
            .with_rank(self.rank))
    }
}

/// Type union operator.
impl<'a> std::ops::BitOr<MarkusType<'a>> for MarkusType<'a> {
    type Output = Result<MarkusType<'a>, Diagnostic>;

    fn bitor(self, rhs: Self) -> Self::Output {
        if rhs.rank != self.rank {
            return Err(Diagnostic::new(DiagnosticKind::TypeMixedRank, None));
        }

        let mut objects = HashSet::with_capacity(self.objects.len() + rhs.objects.len());
        objects.extend(self.objects.into_iter());
        objects.extend(rhs.objects.into_iter());
        objects.shrink_to_fit();

        Ok(MarkusType::new(
            self.space,
            self.rank,
            self.primitive | rhs.primitive,
            objects,
        ))
    }
}

/// Type intersection.
impl<'a> std::ops::BitAnd<MarkusType<'a>> for MarkusType<'a> {
    type Output = Result<MarkusType<'a>, Diagnostic>;

    fn bitand(self, rhs: Self) -> Self::Output {
        if rhs.rank != self.rank {
            return Err(Diagnostic::new(DiagnosticKind::TypeMixedRank, None));
        }

        Ok(MarkusType::new(
            self.space,
            self.rank,
            self.primitive & rhs.primitive,
            self.objects.intersection(&rhs.objects).copied(),
        ))
    }
}

impl<'a> std::ops::Not for MarkusType<'a> {
    type Output = MarkusType<'a>;

    fn not(self) -> Self::Output {
        let any = 0..self.space.next_id();

        MarkusType::new(
            self.space,
            self.rank,
            !self.primitive,
            any.filter(|x| !self.objects.contains(x)),
        )
    }
}

impl<'a> std::cmp::PartialEq for MarkusType<'a> {
    fn eq(&self, other: &MarkusType) -> bool {
        self.rank == other.rank
            && self.primitive == other.primitive
            && self.objects == other.objects
    }
}

impl<'a> std::cmp::Eq for MarkusType<'a> {}

/// a << b: A is a subset of b, returns false if types are not of the same rank.
impl<'a> std::ops::Shl for MarkusType<'a> {
    type Output = bool;

    fn shl(self, rhs: Self) -> Self::Output {
        self.rank == rhs.rank
            && ((self.primitive & rhs.primitive) == self.primitive)
            && self.objects.is_subset(&rhs.objects)
    }
}
