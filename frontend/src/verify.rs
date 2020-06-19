use super::diagnostics::*;
use super::types::*;
use std::collections::HashMap;
use tree_sitter::{Node, Tree, TreeCursor};

pub struct VerifyContext<'a> {
    tree: &'a Tree,
    source: &'a [u16],
    cursor: TreeCursor<'a>,
    nodes: Nodes<'a>,
    space: TypeSpace,
    pub diagnostics: Vec<Diagnostic>,
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

impl<'a> VerifyContext<'a> {
    pub fn new(source: &'a [u16], tree: &'a Tree) -> Self {
        VerifyContext {
            tree,
            source,
            cursor: tree.walk(),
            nodes: Nodes::default(),
            space: TypeSpace::empty(),
            diagnostics: Vec::new(),
        }
    }

    pub fn verify(&mut self) {
        self.extract_nodes();
        self.construct_ts();
    }

    fn extract_nodes(&mut self) {
        let source = self.source;

        for node in self.tree.root_node().children(&mut self.cursor) {
            let node: Node = node;
            let name = match node
                .child_by_field_name("name")
                .map(|id| String::from_utf16_lossy(id.utf16_text(source)))
            {
                Some(n) => n,
                None => {
                    self.diagnostics.push(Diagnostic::new(
                        DiagnosticKind::MissingIdentifier,
                        Some(node.range()),
                    ));
                    continue;
                }
            };

            match match node.kind() {
                "type_declaration" => self.nodes.types.insert(name, node),
                "permission_declaration" => self.nodes.permissions.insert(name, node),
                "query_declaration" => self.nodes.queries.insert(name, node),
                "action_declaration" => self.nodes.actions.insert(name, node),
                _ => unreachable!(),
            } {
                Some(_) => {
                    self.diagnostics.push(Diagnostic::new(
                        DiagnosticKind::NameAlreadyInUse,
                        Some(node.child_by_field_name("name").unwrap().range()),
                    ));
                }
                None => {}
            };
        }
    }

    fn construct_ts(&mut self) {
        let source = self.source;
        let mut nodes = HashMap::<usize, (&String, &Node)>::new();

        // Create a the type graph.
        let (space_graph, topo) = {
            let mut graph = TypeSpaceGraph::new();
            graph.init_builtin().unwrap();

            // Create an empty TypeInfo for each type, report NameAlreadyInUse error for objects
            // with the same name as internal types.
            for (name, node) in &self.nodes.types {
                match graph.add_type(name.clone()) {
                    Ok(id) => {
                        nodes.insert(id, (name, &node));
                    }
                    Err(mut d) => {
                        d.attach_location(node.child_by_field_name("name").unwrap().range());
                        self.diagnostics.push(d);
                    }
                }
            }

            // Create the base graph.
            for (_, &(name, node)) in &nodes {
                for base_node in node.children_by_field_name("base", &mut self.cursor) {
                    let base = String::from_utf16_lossy(base_node.utf16_text(source));
                    match graph.connect(&base, name) {
                        Ok(_) => {}
                        Err(mut err) => {
                            err.attach_location(base_node.range());
                            self.diagnostics.push(err);
                        }
                    }
                }
            }

            let sorted = graph.sorted();
            (graph, sorted)
        };

        // Attach the space graph.
        self.space.update_graph(space_graph);

        // Create fields.
        for obj_id in topo.into_iter() {
            let (_, node) = *nodes.get(&obj_id).unwrap();
            for field_node in node.children_by_field_name("field", &mut self.cursor) {
                match match extract_field_info(source, &field_node) {
                    Ok((name, type_name, optional)) => {
                        match self.space.add_field(obj_id, name, &type_name, optional) {
                            Err(err) => Some(err),
                            Ok(_) => None,
                        }
                    }
                    Err(err) => Some(err),
                } {
                    Some(mut err) => {
                        err.attach_location(field_node.range());
                        self.diagnostics.push(err);
                    }
                    None => {}
                }
            }
        }
    }
}

fn extract_field_info(source: &[u16], node: &Node) -> Result<(String, String, bool), Diagnostic> {
    let name = node
        .child_by_field_name("name")
        .map(|id| String::from_utf16_lossy(id.utf16_text(source)))
        .ok_or(Diagnostic::new(DiagnosticKind::MissingIdentifier, None))?;
    let type_name = node
        .child_by_field_name("field_type")
        .map(|id| String::from_utf16_lossy(id.utf16_text(source)))
        .ok_or(Diagnostic::new(DiagnosticKind::MissingFieldType, None))?;
    let optional = node.child_by_field_name("optional").is_some();
    Ok((name, type_name, optional))
}
