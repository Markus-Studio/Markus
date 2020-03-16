use crate::parser::ast::{Declaration, ValueNode};
use ir::builder::*;
use std::collections::HashMap;

pub fn gen_ir(declarations: &Vec<Declaration>) {
    let mut permissions = HashMap::new();
    let mut queries = Vec::new();

    let type_space = {
        let mut type_builder = TypeSpaceBuilder::new();

        for declaration in declarations {
            match declaration {
                Declaration::Type(type_declaration) => {
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
                Declaration::Permission(permission_declaration) => {
                    let name = permission_declaration
                        .name
                        .as_ref()
                        .unwrap()
                        .value
                        .to_owned();
                    permissions.insert(name, permission_declaration);
                }
                Declaration::Query(query_declaration) => {
                    queries.push(query_declaration);
                }
                _ => {}
            }
        }

        type_builder.build()
    };

    let ir_builder = IRBuilder::new(type_space);

    for query in queries {
        let mut builder = QueryBuilder::new(&ir_builder);
        for parameter in &query.parameters {
            let name = parameter.name.as_ref().unwrap().value.to_owned();
            let type_name = &parameter.type_name.as_ref().unwrap().value;
            let nullable = parameter.optional;
            builder.parameter(name, type_name, nullable);
        }

        // TODO(qti3e) Build guards.

        for pipeline in &query.query.pipelines {
            let name = &pipeline.callee_name.as_ref().unwrap().value as &str;
            match pipeline.arguments.len() {
                1 => match (name, &pipeline.arguments[0]) {
                    ("is", ValueNode::Type(type_reference)) => {
                        let type_name = &type_reference.name.value;
                        builder.is(type_name);
                    }
                    _ => unimplemented!(),
                },
                _ => unimplemented!(),
            }
        }
    }
}
