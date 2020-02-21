use crate::common::Matrix;
use crate::parser::ast::TypeDeclarationNode;
use crate::program::{MarkusTypeInfo, TypeSpace};
use bimap::BiMap;
use std::collections::HashMap;
use std::collections::hash_map::RandomState;
use std::rc::Rc;

type WordId = u32;

pub struct IrTypeSpace {
    pub base_graph: Matrix<bool>,
    pub type_names: BiMap<String, WordId>,
    pub field_names: BiMap<String, WordId>,
    pub objects: HashMap<WordId, IrObjectData>,
    last_type_id: WordId,
    last_field_id: WordId,
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
    pub fn from_type_space(space: &TypeSpace) -> IrTypeSpace {
        let mut object_types: Vec<Rc<TypeDeclarationNode>> = Vec::new();
        for (_, markus_type) in &space.types {
            match markus_type.type_info {
                MarkusTypeInfo::Object { ast, .. } => {
                    object_types.push(ast);
                }
                _ => {}
            }
        }

        let n = object_types.len();

        let mut result = IrTypeSpace {
            base_graph: Matrix::new(n, n, false),
            type_names: BiMap::new(),
            field_names: BiMap::new(),
            objects: HashMap::with_capacity_and_hasher(n, RandomState::new()),
            last_field_id: 0,
            last_type_id: 0,
        };

        for ast in object_types {
            result.add_type(&ast)
        }

        for ast in object_types {
            result.visit_bases(&ast);
        }

        result
    }

    fn add_type(&mut self, ast: &TypeDeclarationNode) {
        let id = self.new_type_id(ast.name.unwrap().value);

    }

    fn visit_bases(&mut self, ast: &TypeDeclarationNode) {

    }

    fn new_type_id(&mut self, name: String) -> WordId {
        match self.type_names.get_by_left(&name) {
            Some(id) => panic!("Type names are supposed to be unique."),
            None => {
                let id = self.last_type_id;
                self.last_type_id += 1;
                self.type_names.insert(String::from(name), id);
                id
            }
        }
    }

    fn new_field_id(&mut self, name: String) -> WordId {
        match self.field_names.get_by_left(&name) {
            Some(id) => *id,
            None => {
                let id = self.last_field_id;
                self.last_field_id += 1;
                self.field_names.insert(String::from(name), id);
                id
            }
        }
    }
}
