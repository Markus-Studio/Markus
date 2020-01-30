extern crate markus;
use markus::parser::ast;
use markus::parser::ast::Program;
use markus::parser::source::Source;
use markus::parser::tokenizer::Span;

#[test]
fn test_type_declaration() {
    {
        let source = "type A {}";
        let mut program = Program::new(Source::new(String::from("foo.x"), source));
        program.parse();
        assert_eq!(program.get_span_data_as_utf8(Span::new(5, 1)), "A");
        assert_eq!(
            program.declarations,
            vec![ast::Declaration::Type(ast::TypeDeclarationNode {
                location: Span::new(0, 9),
                name: Some(ast::IdentifierNode::new(5, 1)),
                bases: vec![],
                fields: vec![]
            })]
        );
    }

    {
        let source = "type A: X, Y {}";
        let mut program = Program::new(Source::new(String::from("foo.x"), source));
        program.parse();
        assert_eq!(program.get_span_data_as_utf8(Span::new(5, 1)), "A");
        assert_eq!(program.get_span_data_as_utf8(Span::new(8, 1)), "X");
        assert_eq!(program.get_span_data_as_utf8(Span::new(11, 1)), "Y");
        assert_eq!(
            program.declarations,
            vec![ast::Declaration::Type(ast::TypeDeclarationNode {
                location: Span::new(0, 15),
                name: Some(ast::IdentifierNode::new(5, 1)),
                bases: vec![
                    ast::IdentifierNode::new(8, 1),
                    ast::IdentifierNode::new(11, 1)
                ],
                fields: vec![]
            })]
        );
    }

    {
        let source = "type A: X, Y { x: number; }";
        let mut program = Program::new(Source::new(String::from("foo.x"), source));
        program.parse();
        assert_eq!(program.get_span_data_as_utf8(Span::new(5, 1)), "A");
        assert_eq!(program.get_span_data_as_utf8(Span::new(8, 1)), "X");
        assert_eq!(program.get_span_data_as_utf8(Span::new(11, 1)), "Y");
        assert_eq!(program.get_span_data_as_utf8(Span::new(15, 1)), "x");
        assert_eq!(program.get_span_data_as_utf8(Span::new(18, 6)), "number");
        assert_eq!(
            program.declarations,
            vec![ast::Declaration::Type(ast::TypeDeclarationNode {
                location: Span::new(0, 27),
                name: Some(ast::IdentifierNode::new(5, 1)),
                bases: vec![
                    ast::IdentifierNode::new(8, 1),
                    ast::IdentifierNode::new(11, 1)
                ],
                fields: vec![ast::TypeFieldNode {
                    location: Span::new(15, 10),
                    nullable: false,
                    name: Some(ast::IdentifierNode::new(15, 1)),
                    type_name: Some(ast::IdentifierNode::new(18, 6)),
                }]
            })]
        );
    }

    {
        let source = "type A: X, Y { x: number; p?: string; }";
        let mut program = Program::new(Source::new(String::from("foo.x"), source));
        program.parse();
        assert_eq!(program.get_span_data_as_utf8(Span::new(5, 1)), "A");
        assert_eq!(program.get_span_data_as_utf8(Span::new(8, 1)), "X");
        assert_eq!(program.get_span_data_as_utf8(Span::new(11, 1)), "Y");
        assert_eq!(program.get_span_data_as_utf8(Span::new(15, 1)), "x");
        assert_eq!(program.get_span_data_as_utf8(Span::new(18, 6)), "number");
        assert_eq!(program.get_span_data_as_utf8(Span::new(26, 1)), "p");
        assert_eq!(program.get_span_data_as_utf8(Span::new(30, 6)), "string");
        assert_eq!(
            program.declarations,
            vec![ast::Declaration::Type(ast::TypeDeclarationNode {
                location: Span::new(0, 39),
                name: Some(ast::IdentifierNode::new(5, 1)),
                bases: vec![
                    ast::IdentifierNode::new(8, 1),
                    ast::IdentifierNode::new(11, 1)
                ],
                fields: vec![
                    ast::TypeFieldNode {
                        location: Span::new(15, 10),
                        nullable: false,
                        name: Some(ast::IdentifierNode::new(15, 1)),
                        type_name: Some(ast::IdentifierNode::new(18, 6)),
                    },
                    ast::TypeFieldNode {
                        location: Span::new(26, 11),
                        nullable: true,
                        name: Some(ast::IdentifierNode::new(26, 1)),
                        type_name: Some(ast::IdentifierNode::new(30, 6)),
                    }
                ]
            })]
        );
    }
}

#[test]
fn test_type_declaration_error_tolerance() {
    {
        let source = "type {} type B {}";
        let mut program = Program::new(Source::new(String::from("foo.x"), source));
        program.parse();
        assert_eq!(program.get_span_data_as_utf8(Span::new(13, 1)), "B");
        assert_eq!(
            program.declarations,
            vec![
                ast::Declaration::Type(ast::TypeDeclarationNode {
                    location: Span::new(0, 7),
                    name: None,
                    bases: vec![],
                    fields: vec![]
                }),
                ast::Declaration::Type(ast::TypeDeclarationNode {
                    location: Span::new(8, 9),
                    name: Some(ast::IdentifierNode::new(13, 1)),
                    bases: vec![],
                    fields: vec![]
                }),
            ]
        );
    }

    {
        let source = "type A: X, , Y {}";
        let mut program = Program::new(Source::new(String::from("foo.x"), source));
        program.parse();
        assert_eq!(program.get_span_data_as_utf8(Span::new(5, 1)), "A");
        assert_eq!(program.get_span_data_as_utf8(Span::new(8, 1)), "X");
        assert_eq!(program.get_span_data_as_utf8(Span::new(13, 1)), "Y");
        assert_eq!(
            program.declarations,
            vec![ast::Declaration::Type(ast::TypeDeclarationNode {
                location: Span::new(0, 17),
                name: Some(ast::IdentifierNode::new(5, 1)),
                bases: vec![
                    ast::IdentifierNode::new(8, 1),
                    ast::IdentifierNode::new(13, 1)
                ],
                fields: vec![]
            })]
        );
    }

    {
        let source = "type A: X, Y { x: ; }";
        let mut program = Program::new(Source::new(String::from("foo.x"), source));
        program.parse();
        assert_eq!(program.get_span_data_as_utf8(Span::new(5, 1)), "A");
        assert_eq!(program.get_span_data_as_utf8(Span::new(8, 1)), "X");
        assert_eq!(program.get_span_data_as_utf8(Span::new(11, 1)), "Y");
        assert_eq!(program.get_span_data_as_utf8(Span::new(15, 1)), "x");
        assert_eq!(
            program.declarations,
            vec![ast::Declaration::Type(ast::TypeDeclarationNode {
                location: Span::new(0, 21),
                name: Some(ast::IdentifierNode::new(5, 1)),
                bases: vec![
                    ast::IdentifierNode::new(8, 1),
                    ast::IdentifierNode::new(11, 1)
                ],
                fields: vec![ast::TypeFieldNode {
                    location: Span::new(15, 4),
                    nullable: false,
                    name: Some(ast::IdentifierNode::new(15, 1)),
                    type_name: None,
                }]
            })]
        );
    }

    {
        let source = "type A: X, Y { x: number; ?: string; }";
        let mut program = Program::new(Source::new(String::from("foo.x"), source));
        program.parse();
        assert_eq!(program.get_span_data_as_utf8(Span::new(5, 1)), "A");
        assert_eq!(program.get_span_data_as_utf8(Span::new(8, 1)), "X");
        assert_eq!(program.get_span_data_as_utf8(Span::new(11, 1)), "Y");
        assert_eq!(program.get_span_data_as_utf8(Span::new(15, 1)), "x");
        assert_eq!(program.get_span_data_as_utf8(Span::new(18, 6)), "number");
        assert_eq!(program.get_span_data_as_utf8(Span::new(29, 6)), "string");
        assert_eq!(
            program.declarations,
            vec![ast::Declaration::Type(ast::TypeDeclarationNode {
                location: Span::new(0, 38),
                name: Some(ast::IdentifierNode::new(5, 1)),
                bases: vec![
                    ast::IdentifierNode::new(8, 1),
                    ast::IdentifierNode::new(11, 1)
                ],
                fields: vec![
                    ast::TypeFieldNode {
                        location: Span::new(15, 10),
                        nullable: false,
                        name: Some(ast::IdentifierNode::new(15, 1)),
                        type_name: Some(ast::IdentifierNode::new(18, 6)),
                    },
                    ast::TypeFieldNode {
                        location: Span::new(26, 10),
                        nullable: true,
                        name: None,
                        type_name: Some(ast::IdentifierNode::new(29, 6)),
                    }
                ]
            })]
        );
    }

    {
        let source = "type A: X, Y { x: number; ?:; y: c; }";
        let mut program = Program::new(Source::new(String::from("foo.x"), source));
        program.parse();
        assert_eq!(program.get_span_data_as_utf8(Span::new(5, 1)), "A");
        assert_eq!(program.get_span_data_as_utf8(Span::new(8, 1)), "X");
        assert_eq!(program.get_span_data_as_utf8(Span::new(11, 1)), "Y");
        assert_eq!(program.get_span_data_as_utf8(Span::new(15, 1)), "x");
        assert_eq!(program.get_span_data_as_utf8(Span::new(18, 6)), "number");
        assert_eq!(program.get_span_data_as_utf8(Span::new(30, 1)), "y");
        assert_eq!(program.get_span_data_as_utf8(Span::new(33, 1)), "c");
        assert_eq!(
            program.declarations,
            vec![ast::Declaration::Type(ast::TypeDeclarationNode {
                location: Span::new(0, 37),
                name: Some(ast::IdentifierNode::new(5, 1)),
                bases: vec![
                    ast::IdentifierNode::new(8, 1),
                    ast::IdentifierNode::new(11, 1)
                ],
                fields: vec![
                    ast::TypeFieldNode {
                        location: Span::new(15, 10),
                        nullable: false,
                        name: Some(ast::IdentifierNode::new(15, 1)),
                        type_name: Some(ast::IdentifierNode::new(18, 6)),
                    },
                    ast::TypeFieldNode {
                        location: Span::new(26, 3),
                        nullable: true,
                        name: None,
                        type_name: None,
                    },
                    ast::TypeFieldNode {
                        location: Span::new(30, 5),
                        nullable: false,
                        name: Some(ast::IdentifierNode::new(30, 1)),
                        type_name: Some(ast::IdentifierNode::new(33, 1)),
                    }
                ]
            })]
        );
    }
}
