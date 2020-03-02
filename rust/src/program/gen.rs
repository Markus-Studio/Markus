use crate::ir::builder::*;
use crate::parser::ast::Declaration;

pub fn gen(declarations: Vec<Declaration>) {
    let type_space = {
        let mut type_builder = TypeSpaceBuilder::new();

        for declaration in &declarations {
            if let Declaration::Type(type_declaration) = declaration {
                let name_id = type_declaration.name.as_ref().unwrap();
                type_builder.begin(name_id.value.to_owned());
                for base in &type_declaration.bases {
                    type_builder.base(base.value.to_owned());
                }
                for field in &type_declaration.fields {
                    let name_id = field.name.as_ref().unwrap();
                    let type_name_id = field.type_name.as_ref().unwrap();
                    let name = name_id.value.to_owned();
                    let field_type = type_name_id.value.to_owned();
                    type_builder.field(name, field_type, field.nullable);
                }
                type_builder.end();
            }
        }

        type_builder.build()
    };
}
