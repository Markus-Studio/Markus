use super::source::Source;
use tree_sitter::{Language, Parser};

#[test]
fn t() {
    let source_code = "type Point { x: number }";
    let source = Source::new("a.markus", source_code);
    let tree = source.get_tree();
    println!("{}", tree.root_node().to_sexp());
}
