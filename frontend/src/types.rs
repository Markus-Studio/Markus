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
pub struct Space {
    /// Maps id of each object to its information.
    objects: HashMap<usize, ObjectInfo>,
    /// A bi-directional map that maps name of each type to its id and vice versa.
    object_names: BiMap<String, usize>,
}

/// A reference to a single type.
pub enum MarkusType {
    Primitive(PrimitiveType),
    Object(usize),
    Union {
        primitives: HashSet<usize>,
        objects: HashSet<usize>,
    },
}

/// Information for an object type, such as its fields and list of its parents.
pub struct ObjectInfo {
    fields: HashMap<String, FieldInfo>,
    parents: HashSet<usize>,
}

pub struct FieldInfo {
    optional: bool,
    dt: MarkusType,
}

impl Space {
    pub fn new() -> Space {
        Space {
            objects: HashMap::new(),
            object_names: BiMap::new(),
        }
    }

    pub fn add_object(name: String, info: ObjectInfo) -> Result<(), Diagnostic> {
        Ok(())
    }
}

impl MarkusType {}
