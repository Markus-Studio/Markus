mod ast;

fn main() -> Result<(), Box<dyn std::error::Error + 'static>> {
    let source = "
enum X {
    string name;
}
    ";

    let mut x = ast::source::Source::new(String::from("x.markus"), source);

    Ok(())
}
