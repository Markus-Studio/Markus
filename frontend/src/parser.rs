use super::shared::Position;
use super::source::{Source, TextEdit};

#[test]
fn t() {
    let source_code = "type 
    {
        x: number,
        y: number
    }
    
    type P {
        s: name,
    }";

    let mut source = Source::new("a.markus", source_code);
    let tree = source.get_tree();

    println!("{}", tree.root_node().to_sexp());
    let e0 = TextEdit::insert(Position::new(0, 5), "Point".to_string());
    source.apply_edits(&mut vec![e0]);

    let tree = source.get_tree();
    println!("{}", tree.root_node().to_sexp());

    let mut cursor = tree.walk();
    println!("{}", cursor.node().to_sexp());

    assert!(cursor.goto_first_child());
    println!("{}", cursor.node().is_error());
    println!("{}", cursor.node().to_sexp());

    let name = cursor.node().child_by_field_name("name").unwrap();
    println!(
        "is_error: {} is_missing: {}",
        name.is_error(),
        name.is_missing()
    );
    println!("{}", name.to_sexp());
}
