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
        assert_eq!(
            program.declarations,
            vec![ast::Declaration::Type(ast::TypeDeclarationNode {
                location: Span::new(0, 9),
                name: Some(ast::IdentifierNode::new(5, "A")),
                bases: vec![],
                fields: vec![]
            })]
        );
    }

    {
        let source = "type A: X, Y {}";
        let mut program = Program::new(Source::new(String::from("foo.x"), source));
        program.parse();
        assert_eq!(
            program.declarations,
            vec![ast::Declaration::Type(ast::TypeDeclarationNode {
                location: Span::new(0, 15),
                name: Some(ast::IdentifierNode::new(5, "A")),
                bases: vec![
                    ast::IdentifierNode::new(8, "X"),
                    ast::IdentifierNode::new(11, "Y")
                ],
                fields: vec![]
            })]
        );
    }

    {
        let source = "type A: X, Y { x: number; }";
        let mut program = Program::new(Source::new(String::from("foo.x"), source));
        program.parse();
        assert_eq!(
            program.declarations,
            vec![ast::Declaration::Type(ast::TypeDeclarationNode {
                location: Span::new(0, 27),
                name: Some(ast::IdentifierNode::new(5, "A")),
                bases: vec![
                    ast::IdentifierNode::new(8, "X"),
                    ast::IdentifierNode::new(11, "Y")
                ],
                fields: vec![ast::TypeFieldNode {
                    location: Span::new(15, 10),
                    nullable: false,
                    name: Some(ast::IdentifierNode::new(15, "x")),
                    type_name: Some(ast::IdentifierNode::new(18, "number")),
                }]
            })]
        );
    }

    {
        let source = "type A: X, Y { x: number; p?: string; }";
        let mut program = Program::new(Source::new(String::from("foo.x"), source));
        program.parse();
        assert_eq!(
            program.declarations,
            vec![ast::Declaration::Type(ast::TypeDeclarationNode {
                location: Span::new(0, 39),
                name: Some(ast::IdentifierNode::new(5, "A")),
                bases: vec![
                    ast::IdentifierNode::new(8, "X"),
                    ast::IdentifierNode::new(11, "Y")
                ],
                fields: vec![
                    ast::TypeFieldNode {
                        location: Span::new(15, 10),
                        nullable: false,
                        name: Some(ast::IdentifierNode::new(15, "x")),
                        type_name: Some(ast::IdentifierNode::new(18, "number")),
                    },
                    ast::TypeFieldNode {
                        location: Span::new(26, 11),
                        nullable: true,
                        name: Some(ast::IdentifierNode::new(26, "p")),
                        type_name: Some(ast::IdentifierNode::new(30, "string")),
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
                    name: Some(ast::IdentifierNode::new(13, "B")),
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
        assert_eq!(
            program.declarations,
            vec![ast::Declaration::Type(ast::TypeDeclarationNode {
                location: Span::new(0, 17),
                name: Some(ast::IdentifierNode::new(5, "A")),
                bases: vec![
                    ast::IdentifierNode::new(8, "X"),
                    ast::IdentifierNode::new(13, "Y")
                ],
                fields: vec![]
            })]
        );
    }

    {
        let source = "type A: X, Y { x: ; }";
        let mut program = Program::new(Source::new(String::from("foo.x"), source));
        program.parse();
        assert_eq!(
            program.declarations,
            vec![ast::Declaration::Type(ast::TypeDeclarationNode {
                location: Span::new(0, 21),
                name: Some(ast::IdentifierNode::new(5, "A")),
                bases: vec![
                    ast::IdentifierNode::new(8, "X"),
                    ast::IdentifierNode::new(11, "Y")
                ],
                fields: vec![ast::TypeFieldNode {
                    location: Span::new(15, 4),
                    nullable: false,
                    name: Some(ast::IdentifierNode::new(15, "x")),
                    type_name: None,
                }]
            })]
        );
    }

    {
        let source = "type A: X, Y { x: number; ?: string; }";
        let mut program = Program::new(Source::new(String::from("foo.x"), source));
        program.parse();
        assert_eq!(
            program.declarations,
            vec![ast::Declaration::Type(ast::TypeDeclarationNode {
                location: Span::new(0, 38),
                name: Some(ast::IdentifierNode::new(5, "A")),
                bases: vec![
                    ast::IdentifierNode::new(8, "X"),
                    ast::IdentifierNode::new(11, "Y")
                ],
                fields: vec![
                    ast::TypeFieldNode {
                        location: Span::new(15, 10),
                        nullable: false,
                        name: Some(ast::IdentifierNode::new(15, "x")),
                        type_name: Some(ast::IdentifierNode::new(18, "number")),
                    },
                    ast::TypeFieldNode {
                        location: Span::new(26, 10),
                        nullable: true,
                        name: None,
                        type_name: Some(ast::IdentifierNode::new(29, "string")),
                    }
                ]
            })]
        );
    }

    {
        let source = "type A: X, Y { x: number; ?:; y: c; }";
        let mut program = Program::new(Source::new(String::from("foo.x"), source));
        program.parse();
        assert_eq!(
            program.declarations,
            vec![ast::Declaration::Type(ast::TypeDeclarationNode {
                location: Span::new(0, 37),
                name: Some(ast::IdentifierNode::new(5, "A")),
                bases: vec![
                    ast::IdentifierNode::new(8, "X"),
                    ast::IdentifierNode::new(11, "Y")
                ],
                fields: vec![
                    ast::TypeFieldNode {
                        location: Span::new(15, 10),
                        nullable: false,
                        name: Some(ast::IdentifierNode::new(15, "x")),
                        type_name: Some(ast::IdentifierNode::new(18, "number")),
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
                        name: Some(ast::IdentifierNode::new(30, "y")),
                        type_name: Some(ast::IdentifierNode::new(33, "c")),
                    }
                ]
            })]
        );
    }

    {
        let source = "type A: X  Y { x  number  p?  string";
        let mut program = Program::new(Source::new(String::from("foo.x"), source));
        program.parse();
        assert_eq!(
            program.declarations,
            vec![ast::Declaration::Type(ast::TypeDeclarationNode {
                location: Span::new(0, 36),
                name: Some(ast::IdentifierNode::new(5, "A")),
                bases: vec![
                    ast::IdentifierNode::new(8, "X"),
                    ast::IdentifierNode::new(11, "Y")
                ],
                fields: vec![
                    ast::TypeFieldNode {
                        location: Span::new(15, 9),
                        nullable: false,
                        name: Some(ast::IdentifierNode::new(15, "x")),
                        type_name: Some(ast::IdentifierNode::new(18, "number")),
                    },
                    ast::TypeFieldNode {
                        location: Span::new(26, 10),
                        nullable: true,
                        name: Some(ast::IdentifierNode::new(26, "p")),
                        type_name: Some(ast::IdentifierNode::new(30, "string")),
                    }
                ]
            })]
        );
    }
}
