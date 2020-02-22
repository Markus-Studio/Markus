use crate::common::Matrix;
use crate::parser::ast::TypeDeclarationNode;
use crate::program::{MarkusTypeInfo, TypeSpace};
use bimap::BiMap;
use std::collections::hash_map::RandomState;
use std::collections::HashMap;
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
            match &markus_type.type_info {
                MarkusTypeInfo::Object { ast, .. } => {
                    object_types.push(ast.clone());
                }
                _ => {}
            }
        }

        let reserved = 10;
        let n = object_types.len();

        let mut result = IrTypeSpace {
            base_graph: Matrix::new(n + reserved, n + reserved, false),
            type_names: BiMap::new(),
            field_names: BiMap::new(),
            objects: HashMap::with_capacity_and_hasher(n, RandomState::new()),
            last_field_id: 0,
            last_type_id: 0,
        };

        // Internals.
        result.new_type_id(&String::from("user"));
        result.new_type_id(&String::from("geo"));
        result.last_type_id = reserved as u32;

        object_types.sort_by(|a, b| {
            let name_a = &a.name.as_ref().unwrap().value;
            let name_b = &b.name.as_ref().unwrap().value;
            name_a.partial_cmp(name_b).unwrap()
        });

        let objects_map: HashMap<String, Rc<TypeDeclarationNode>> = object_types
            .iter()
            .map(|o| (o.name.as_ref().unwrap().value.clone(), o.clone()))
            .collect();

        for ast in &object_types {
            result.add_type(&ast)
        }

        for ast in &object_types {
            let name = &ast.name.as_ref().unwrap().value;
            let id = result.new_type_id(name);
            result.visit_bases(&objects_map, id, &ast);
        }

        for i in 0..reserved {
            result.base_graph.set(i, i, true);
        }

        result
    }

    fn add_type(&mut self, ast: &TypeDeclarationNode) {
        let name = &ast.name.as_ref().unwrap().value;
        let id = self.new_type_id(name);
        let mut fields = HashMap::<WordId, (IrType, bool)>::new();
        for field in &ast.fields {
            let field_name = &field.name.as_ref().unwrap().value;
            let type_name = &field.type_name.as_ref().unwrap().value;
            let field_id = self.new_field_id(field_name);
            let field_type = self.get_type(type_name);
            fields.insert(field_id, (field_type, field.nullable));
        }
        self.objects.insert(id, fields);
    }

    fn visit_bases(
        &mut self,
        objects_map: &HashMap<String, Rc<TypeDeclarationNode>>,
        root: WordId,
        ast: &TypeDeclarationNode,
    ) {
        for base in &ast.bases {
            let base_name = &base.value;
            let base_id = self.new_type_id(base_name);
            self.base_graph.set(root as usize, base_id as usize, true);
            match objects_map.get(base_name) {
                Some(base_ast) => {
                    self.visit_bases(objects_map, root, base_ast);
                }
                None => {} // Internal objects.
            }
        }
    }

    fn get_type(&mut self, name: &str) -> IrType {
        match name {
            "i32" => IrType::I32,
            "i64" => IrType::I64,
            "u32" => IrType::U32,
            "u64" => IrType::U64,
            "f32" => IrType::F32,
            "f64" => IrType::F64,
            "bool" => IrType::Bool,
            "string" => IrType::Str,
            _ => IrType::Object(self.new_type_id(&String::from(name))),
        }
    }

    fn new_type_id(&mut self, name: &String) -> WordId {
        match self.type_names.get_by_left(&name) {
            Some(id) => *id,
            None => {
                let id = self.last_type_id;
                self.last_type_id += 1;
                self.type_names.insert(String::from(name), id);
                id
            }
        }
    }

    fn new_field_id(&mut self, name: &String) -> WordId {
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
