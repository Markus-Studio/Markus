use crate::program::TypeSpace;
use bimap::BiMap;
use std::collections::HashMap;

type WordId = u32;

pub struct IrTypeSpace {
    pub is_lookup_matrix: Vec<Vec<bool>>,
    pub type_names: BiMap<String, WordId>,
    pub field_names: BiMap<String, WordId>,
    pub objects: IrObjectData,
    last_type_id: WordId,
    last_field_names: WordId,
}

type IrObjectData = HashMap<WordId, (IrType, bool)>;

pub enum IrType {
    Null,
    I32,
    I64,
    U32,
    U64,
    F32,
    F64,
    Str,
    Bool,
    Object(WordId),
}

impl IrTypeSpace {
    pub fn from_type_space(space: &TypeSpace) -> IrTypeSpace {}
}
