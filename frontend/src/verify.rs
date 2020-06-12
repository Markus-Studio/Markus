use super::types::*;
use std::collections::HashMap;
use tree_sitter::{Node, Tree};

pub fn verify(tree: &Tree) {
    let nodes = Nodes::from_tree(tree);
    let space = create_type_space(tree);
}

pub fn create_type_space<'a>(tree: &Tree) -> Space<'a> {
    let space = Space::new();

    space
}

struct Nodes<'a> {
    pub types: HashMap<String, Node<'a>>,
    pub permissions: HashMap<String, Node<'a>>,
    pub queries: HashMap<String, Node<'a>>,
    pub actions: HashMap<String, Node<'a>>,
}

impl<'a> Default for Nodes<'a> {
    fn default() -> Self {
        Nodes {
            types: HashMap::new(),
            permissions: HashMap::new(),
            queries: HashMap::new(),
            actions: HashMap::new(),
        }
    }
}

impl<'a> Nodes<'a> {
    pub fn from_tree(tree: &'a Tree) -> Nodes<'a> {
        let mut nodes = Nodes::default();
        let mut cursor = tree.walk();

        for node in tree.root_node().children(&mut cursor) {
            let node: Node = node;
            let name = node.child_by_field_name("name");
        }

        nodes
    }
}
