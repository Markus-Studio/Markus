use super::types::*;
use tree_sitter::{Tree, TreeCursor};

pub fn verify(tree: &Tree) {
    // Steps:
    // 1. Create the typespace
}

pub fn create_type_space<'a>(tree: &Tree) -> Space<'a> {
    let space = Space::new();
    let mut cursor = tree.walk();

    cursor.goto_first_child();
    println!("{}", cursor.node().to_sexp());
    cursor.goto_next_sibling();
    println!("{}", cursor.node().to_sexp());

    space
}
