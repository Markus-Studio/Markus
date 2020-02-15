extern crate markus;
use ast::*;
use markus::parser::*;
use markus::program::*;
use std::rc::Rc;

// Editor tests taken from microsoft/vscode-languageserver-node

#[cfg(test)]
fn get_source(data: &str) -> Source {
    Source::new("foo://bar", data)
}

#[test]
fn source_edit_inserts_0() {
    let mut source = get_source("012345678901234567890123456789");
    assert_eq!(
        source.apply_edits(&mut vec![TextEdit::insert(
            Position::new(0, 0),
            String::from("Hello"),
        )]),
        TextEditResult::new(0, 0, 5)
    );
    assert_eq!(
        "Hello012345678901234567890123456789",
        source.get_content_utf8()
    );
}

#[test]
fn source_edit_inserts_1() {
    let mut source = get_source("012345678901234567890123456789");
    assert_eq!(
        source.apply_edits(&mut vec![TextEdit::insert(
            Position::new(0, 1),
            String::from("Hello"),
        )]),
        TextEditResult::new(1, 1, 5)
    );
    assert_eq!(
        "0Hello12345678901234567890123456789",
        source.get_content_utf8()
    );
}

#[test]
fn source_edit_inserts_2() {
    let mut source = get_source("012345678901234567890123456789");
    assert_eq!(
        source.apply_edits(&mut vec![
            TextEdit::insert(Position::new(0, 1), String::from("Hello")),
            TextEdit::insert(Position::new(0, 1), String::from("World")),
        ]),
        TextEditResult::new(1, 1, 10)
    );
    assert_eq!(
        "0HelloWorld12345678901234567890123456789",
        source.get_content_utf8()
    );
}

#[test]
fn source_edit_inserts_3() {
    let mut source = get_source("012345678901234567890123456789");
    assert_eq!(
        source.apply_edits(&mut vec![
            TextEdit::insert(Position::new(0, 2), String::from("One")),
            TextEdit::insert(Position::new(0, 1), String::from("Hello")),
            TextEdit::insert(Position::new(0, 1), String::from("World")),
            TextEdit::insert(Position::new(0, 2), String::from("Two")),
            TextEdit::insert(Position::new(0, 2), String::from("Three")),
        ]),
        TextEditResult::new(1, 2, 21)
    );
    assert_eq!(
        "0HelloWorld1OneTwoThree2345678901234567890123456789",
        source.get_content_utf8()
    );
}

#[test]
fn source_edit_replace_0() {
    let mut source = get_source("012345678901234567890123456789");
    assert_eq!(
        source.apply_edits(&mut vec![TextEdit::replace(
            Position::new(0, 3),
            Position::new(0, 6),
            String::from("Hello"),
        )]),
        TextEditResult::new(3, 6, 2)
    );
    assert_eq!(
        "012Hello678901234567890123456789",
        source.get_content_utf8()
    );
}

#[test]
fn source_edit_replace_1() {
    let mut source = get_source("012345678901234567890123456789");
    assert_eq!(
        source.apply_edits(&mut vec![
            TextEdit::replace(
                Position::new(0, 3),
                Position::new(0, 6),
                String::from("Hello"),
            ),
            TextEdit::replace(
                Position::new(0, 6),
                Position::new(0, 9),
                String::from("World"),
            ),
        ]),
        TextEditResult::new(3, 9, 4)
    );
    assert_eq!(
        "012HelloWorld901234567890123456789",
        source.get_content_utf8()
    );
}

#[test]
fn source_edit_replace_2() {
    let mut source = get_source("012345678901234567890123456789");
    assert_eq!(
        source.apply_edits(&mut vec![
            TextEdit::replace(
                Position::new(0, 3),
                Position::new(0, 6),
                String::from("Hello"),
            ),
            TextEdit::insert(Position::new(0, 6), String::from("World")),
        ]),
        TextEditResult::new(3, 6, 7)
    );
    assert_eq!(
        "012HelloWorld678901234567890123456789",
        source.get_content_utf8()
    );
}

#[test]
fn source_edit_replace_3() {
    let mut source = get_source("012345678901234567890123456789");
    assert_eq!(
        source.apply_edits(&mut vec![
            TextEdit::insert(Position::new(0, 6), String::from("World")),
            TextEdit::replace(
                Position::new(0, 3),
                Position::new(0, 6),
                String::from("Hello"),
            ),
        ]),
        TextEditResult::new(3, 6, 7)
    );
    assert_eq!(
        "012HelloWorld678901234567890123456789",
        source.get_content_utf8()
    );
}

#[test]
fn source_edit_replace_4() {
    let mut source = get_source("012345678901234567890123456789");
    assert_eq!(
        source.apply_edits(&mut vec![
            TextEdit::insert(Position::new(0, 3), String::from("World")),
            TextEdit::replace(
                Position::new(0, 3),
                Position::new(0, 6),
                String::from("Hello"),
            ),
        ]),
        TextEditResult::new(3, 6, 7)
    );
    assert_eq!(
        "012WorldHello678901234567890123456789",
        source.get_content_utf8()
    );
}

#[test]
fn source_edit_multiline() {
    let mut source = get_source("0\n1\n2\n3\n4");
    assert_eq!(
        source.apply_edits(&mut vec![
            TextEdit::replace(
                Position::new(2, 0),
                Position::new(3, 0),
                String::from("Hello"),
            ),
            TextEdit::insert(Position::new(1, 1), String::from("World")),
        ]),
        TextEditResult::new(3, 6, 8)
    );
    assert_eq!("0\n1World\nHello3\n4", source.get_content_utf8());
}

#[test]
fn tokenizer_basic() {
    let source = "query x { }";
    let data: Vec<u16> = source.encode_utf16().collect();
    let tokens: Vec<Token> = Tokenizer::new(&data, 0).collect();
    assert_eq!(tokens.len(), 4);
    assert_eq!(tokens[0].kind, TokenKind::QueryKeyword);
    assert!(!tokens[2].is_identifer());

    assert!(!tokens[0].compare_identifier(&data, "Hello World"));
    assert!(tokens[1].compare_identifier(&data, "x"));
    // TODO(qti3e) Test other tokens too.
}

#[test]
fn ast_type_declaration_01() {
    let source = "type A {}";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    assert!(program.is_good());
    assert_eq!(
        program.declarations,
        vec![Declaration::Type(Rc::new(TypeDeclarationNode {
            location: Span::new(0, 9),
            name: Some(IdentifierNode::new(5, "A")),
            bases: vec![],
            fields: vec![]
        }))]
    );
}

#[test]
fn ast_type_declaration_02() {
    let source = "type A: X, Y {}";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    assert!(program.is_good());
    assert_eq!(
        program.declarations,
        vec![Declaration::Type(Rc::new(TypeDeclarationNode {
            location: Span::new(0, 15),
            name: Some(IdentifierNode::new(5, "A")),
            bases: vec![IdentifierNode::new(8, "X"), IdentifierNode::new(11, "Y")],
            fields: vec![]
        }))]
    );
}

#[test]
fn ast_type_declaration_03() {
    let source = "type A: X, Y { x: number; }";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    assert!(program.is_good());
    assert_eq!(
        program.declarations,
        vec![Declaration::Type(Rc::new(TypeDeclarationNode {
            location: Span::new(0, 27),
            name: Some(IdentifierNode::new(5, "A")),
            bases: vec![IdentifierNode::new(8, "X"), IdentifierNode::new(11, "Y")],
            fields: vec![TypeFieldNode {
                location: Span::new(15, 10),
                nullable: false,
                name: Some(IdentifierNode::new(15, "x")),
                type_name: Some(IdentifierNode::new(18, "number")),
            }]
        }))]
    );
}

#[test]
fn ast_type_declaration_04() {
    let source = "type A: X, Y { x: number; p?: string; }";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    assert!(program.is_good());
    assert_eq!(
        program.declarations,
        vec![Declaration::Type(Rc::new(TypeDeclarationNode {
            location: Span::new(0, 39),
            name: Some(IdentifierNode::new(5, "A")),
            bases: vec![IdentifierNode::new(8, "X"), IdentifierNode::new(11, "Y")],
            fields: vec![
                TypeFieldNode {
                    location: Span::new(15, 10),
                    nullable: false,
                    name: Some(IdentifierNode::new(15, "x")),
                    type_name: Some(IdentifierNode::new(18, "number")),
                },
                TypeFieldNode {
                    location: Span::new(26, 11),
                    nullable: true,
                    name: Some(IdentifierNode::new(26, "p")),
                    type_name: Some(IdentifierNode::new(30, "string")),
                }
            ]
        }))]
    );
}

#[test]
fn ast_type_declaration_error_tolerance_01() {
    let source = "type {} type B {}";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    assert!(!program.is_good());
    assert_eq!(
        program.declarations,
        vec![
            Declaration::Type(Rc::new(TypeDeclarationNode {
                location: Span::new(0, 7),
                name: None,
                bases: vec![],
                fields: vec![]
            })),
            Declaration::Type(Rc::new(TypeDeclarationNode {
                location: Span::new(8, 9),
                name: Some(IdentifierNode::new(13, "B")),
                bases: vec![],
                fields: vec![]
            })),
        ]
    );
}

#[test]
fn ast_type_declaration_error_tolerance_02() {
    let source = "type A: X, , Y {}";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    assert!(!program.is_good());
    assert_eq!(
        program.declarations,
        vec![Declaration::Type(Rc::new(TypeDeclarationNode {
            location: Span::new(0, 17),
            name: Some(IdentifierNode::new(5, "A")),
            bases: vec![IdentifierNode::new(8, "X"), IdentifierNode::new(13, "Y")],
            fields: vec![]
        }))]
    );
}

#[test]
fn ast_type_declaration_error_tolerance_03() {
    let source = "type A: X, Y { x: ; }";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    assert!(!program.is_good());
    assert_eq!(
        program.declarations,
        vec![Declaration::Type(Rc::new(TypeDeclarationNode {
            location: Span::new(0, 21),
            name: Some(IdentifierNode::new(5, "A")),
            bases: vec![IdentifierNode::new(8, "X"), IdentifierNode::new(11, "Y")],
            fields: vec![TypeFieldNode {
                location: Span::new(15, 4),
                nullable: false,
                name: Some(IdentifierNode::new(15, "x")),
                type_name: None,
            }]
        }))]
    );
}

#[test]
fn ast_type_declaration_error_tolerance_04() {
    let source = "type A: X, Y { x: number; ?: string; }";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    assert!(!program.is_good());
    assert_eq!(
        program.declarations,
        vec![Declaration::Type(Rc::new(TypeDeclarationNode {
            location: Span::new(0, 38),
            name: Some(IdentifierNode::new(5, "A")),
            bases: vec![IdentifierNode::new(8, "X"), IdentifierNode::new(11, "Y")],
            fields: vec![
                TypeFieldNode {
                    location: Span::new(15, 10),
                    nullable: false,
                    name: Some(IdentifierNode::new(15, "x")),
                    type_name: Some(IdentifierNode::new(18, "number")),
                },
                TypeFieldNode {
                    location: Span::new(26, 10),
                    nullable: true,
                    name: None,
                    type_name: Some(IdentifierNode::new(29, "string")),
                }
            ]
        }))]
    );
}

#[test]
fn ast_type_declaration_error_tolerance_05() {
    let source = "type A: X, Y { x: number; ?:; y: c; }";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    assert!(!program.is_good());
    assert_eq!(
        program.declarations,
        vec![Declaration::Type(Rc::new(TypeDeclarationNode {
            location: Span::new(0, 37),
            name: Some(IdentifierNode::new(5, "A")),
            bases: vec![IdentifierNode::new(8, "X"), IdentifierNode::new(11, "Y")],
            fields: vec![
                TypeFieldNode {
                    location: Span::new(15, 10),
                    nullable: false,
                    name: Some(IdentifierNode::new(15, "x")),
                    type_name: Some(IdentifierNode::new(18, "number")),
                },
                TypeFieldNode {
                    location: Span::new(26, 3),
                    nullable: true,
                    name: None,
                    type_name: None,
                },
                TypeFieldNode {
                    location: Span::new(30, 5),
                    nullable: false,
                    name: Some(IdentifierNode::new(30, "y")),
                    type_name: Some(IdentifierNode::new(33, "c")),
                }
            ]
        }))]
    );
}

#[test]
fn ast_type_declaration_error_tolerance_06() {
    let source = "type A: X  Y { x  number  p?  string";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    assert!(!program.is_good());
    assert_eq!(
        program.declarations,
        vec![Declaration::Type(Rc::new(TypeDeclarationNode {
            location: Span::new(0, 36),
            name: Some(IdentifierNode::new(5, "A")),
            bases: vec![IdentifierNode::new(8, "X"), IdentifierNode::new(11, "Y")],
            fields: vec![
                TypeFieldNode {
                    location: Span::new(15, 9),
                    nullable: false,
                    name: Some(IdentifierNode::new(15, "x")),
                    type_name: Some(IdentifierNode::new(18, "number")),
                },
                TypeFieldNode {
                    location: Span::new(26, 10),
                    nullable: true,
                    name: Some(IdentifierNode::new(26, "p")),
                    type_name: Some(IdentifierNode::new(30, "string")),
                }
            ]
        }))]
    );
}

#[test]
fn ast_query_declaration_01() {
    let source = "query X() {}";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    assert!(program.is_good());
    assert_eq!(
        program.declarations,
        vec![Declaration::Query(Rc::new(QueryDeclarationNode {
            location: Span::new(0, 12),
            name: Some(IdentifierNode::new(6, "X")),
            parameters: vec![],
            query: QueryNode {
                location: Span::new(10, 2),
                pipelines: vec![]
            }
        }))]
    )
}

#[test]
fn ast_query_declaration_02() {
    let source = "query X($a: X, $b: Y) {}";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    assert!(program.is_good());
    assert_eq!(
        program.declarations,
        vec![Declaration::Query(Rc::new(QueryDeclarationNode {
            location: Span::new(0, 24),
            name: Some(IdentifierNode::new(6, "X")),
            parameters: vec![
                ParameterNode {
                    location: Span::new(8, 5),
                    optional: false,
                    name: Some(IdentifierNode::new(8, "$a")),
                    type_name: Some(IdentifierNode::new(12, "X"))
                },
                ParameterNode {
                    location: Span::new(15, 5),
                    optional: false,
                    name: Some(IdentifierNode::new(15, "$b")),
                    type_name: Some(IdentifierNode::new(19, "Y"))
                }
            ],
            query: QueryNode {
                location: Span::new(22, 2),
                pipelines: vec![]
            }
        }))]
    )
}

#[test]
fn ast_query_declaration_03() {
    let source = "query X() {a()}";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    assert!(program.is_good());
    assert_eq!(
        program.declarations,
        vec![Declaration::Query(Rc::new(QueryDeclarationNode {
            location: Span::new(0, 15),
            name: Some(IdentifierNode::new(6, "X")),
            parameters: vec![],
            query: QueryNode {
                location: Span::new(10, 5),
                pipelines: vec![CallNode {
                    location: Span::new(11, 3),
                    callee_name: Some(IdentifierNode::new(11, "a")),
                    arguments: vec![]
                }]
            }
        }))]
    )
}

fn get_value_ast<'a>(program: &'a Program) -> &'a ValueNode {
    assert_eq!(program.declarations.len(), 1);
    match &program.declarations[0] {
        Declaration::Query(query) => {
            assert_eq!(query.query.pipelines.len(), 1);
            assert_eq!(query.query.pipelines[0].arguments.len(), 1);
            &query.query.pipelines[0].arguments[0]
        }
        _ => panic!("Expected query declaration"),
    }
}

#[test]
fn ast_int_literal() {
    let source = "query X() {a(53)}";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    let ast = get_value_ast(&program);
    assert_eq!(
        *ast,
        ValueNode::Int(IntLiteralNode {
            location: Span::new(13, 2),
            neg: false
        })
    );
}

#[test]
fn ast_neg_int_literal() {
    let source = "query X() {a(-3)}";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    let ast = get_value_ast(&program);
    assert_eq!(
        *ast,
        ValueNode::Int(IntLiteralNode {
            location: Span::new(13, 2),
            neg: true
        })
    );
}

#[test]
fn ast_float_literal() {
    let source = "query X() {a(53.2)}";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    let ast = get_value_ast(&program);
    assert_eq!(
        *ast,
        ValueNode::Float(FloatLiteralNode {
            location: Span::new(13, 4)
        })
    );
}

#[test]
fn ast_boolean_true_literal() {
    let source = "query X() {a(true)}";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    let ast = get_value_ast(&program);
    assert_eq!(
        *ast,
        ValueNode::Boolean(BooleanLiteralNode {
            location: Span::new(13, 4)
        })
    );
}

#[test]
fn ast_boolean_false_literal() {
    let source = "query X() {a(false)}";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    let ast = get_value_ast(&program);
    assert_eq!(
        *ast,
        ValueNode::Boolean(BooleanLiteralNode {
            location: Span::new(13, 5)
        })
    );
}

#[test]
fn ast_type_reference() {
    let source = "query X() {a(Ya_)}";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    let ast = get_value_ast(&program);
    assert_eq!(
        *ast,
        ValueNode::Type(TypeReferenceNode {
            location: Span::new(13, 3),
            name: IdentifierNode::new(13, "Ya_")
        })
    );
}

#[test]
fn ast_field_current() {
    let source = "query X() {a(.x)}";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    let ast = get_value_ast(&program);
    assert_eq!(
        *ast,
        ValueNode::Access(AccessNode {
            location: Span::new(13, 2),
            base: VariableReferenceNode::Current,
            parts: vec![IdentifierNode::new(14, "x")]
        })
    );
}

#[test]
fn ast_field_parameter() {
    let source = "query X() {a($a.x)}";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    let ast = get_value_ast(&program);
    assert_eq!(
        *ast,
        ValueNode::Access(AccessNode {
            location: Span::new(13, 4),
            base: VariableReferenceNode::Variable(IdentifierNode::new(13, "$a")),
            parts: vec![IdentifierNode::new(16, "x")]
        })
    );
}

#[test]
fn ast_field_internal() {
    let source = "query X() {a(%a.x)}";
    let mut program = Program::new(Source::new("foo.x", source));
    program.parse();
    let ast = get_value_ast(&program);
    assert_eq!(
        *ast,
        ValueNode::Access(AccessNode {
            location: Span::new(13, 4),
            base: VariableReferenceNode::Internal(IdentifierNode::new(13, "%a")),
            parts: vec![IdentifierNode::new(16, "x")]
        })
    );
}
