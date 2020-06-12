use super::diagnostics::*;
use super::types;
use super::types::*;
use daggy;
use petgraph;
use std::collections::HashMap;
use tree_sitter::{Node, Tree, TreeCursor};

type TypeDag = daggy::Dag<usize, (), usize>;

pub struct VerifyContext<'a> {
    tree: &'a Tree,
    source: &'a [u16],
    cursor: TreeCursor<'a>,
    nodes: Nodes<'a>,
    space: types::Space<'a>,
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
            space: types::Space::new(),
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
        let mut nodes = Vec::<&Node>::new();
        let mut dag = daggy::Dag::<usize, (), usize>::new();

        // Create an empty TypeInfo for each type, report NameAlreadyInUse error for objects
        // with the same name as internal types.
        for (name, node) in &self.nodes.types {
            match self.space.add_object(name.clone(), ObjectInfo::new()) {
                Ok(id) => {
                    nodes.push(&node);
                    assert_eq!(dag.add_node(id).index(), id);
                }
                Err(mut d) => {
                    d.attach_location(node.child_by_field_name("name").unwrap().range());
                    self.diagnostics.push(d);
                }
            }
        }

        // Create the base graph.
        for (obj_id, node) in self.space.object_ids().zip(nodes.iter().copied()) {
            for base_node in node.children_by_field_name("base", &mut self.cursor) {
                let base = String::from_utf16_lossy(base_node.utf16_text(source));
                match add_base(&mut self.space, obj_id, &base, &mut dag) {
                    Ok(_) => {}
                    Err(mut err) => {
                        err.attach_location(base_node.range());
                        self.diagnostics.push(err);
                    }
                }
            }
        }

        // Create fields.
        let graph = dag.graph();
        let sorted = petgraph::algo::toposort(graph, None).unwrap();

        for id in sorted.iter().rev() {
            let id = id.index();
            println!("{} {}", id, self.space.get_object_name(&id).unwrap());
        }
    }
}

#[inline]
fn add_base(
    space: &mut types::Space,
    obj_id: usize,
    base: &String,
    dag: &mut TypeDag,
) -> Result<(), Diagnostic> {
    let base = space.get_object_id(base);
    let info = space.get_object_by_id_mut(&obj_id).unwrap();

    if let Some(base_id) = base {
        if base_id == obj_id {
            return Err(Diagnostic::new(DiagnosticKind::CircularBaseGraph, None));
        }

        match dag.add_edge(
            daggy::NodeIndex::<usize>::new(obj_id),
            daggy::NodeIndex::<usize>::new(base_id),
            (),
        ) {
            Ok(_) => {
                info.add_base(base_id);
                Ok(())
            }
            Err(_) => Err(Diagnostic::new(DiagnosticKind::CircularBaseGraph, None)),
        }
    } else {
        Err(Diagnostic::new(DiagnosticKind::CannotResolveName, None))
    }
}
