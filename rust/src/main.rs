mod parser;

fn main() -> Result<(), Box<dyn std::error::Error + 'static>> {
    let source = "query a($a: X) {}";

    let x = parser::source::Source::new(String::from("x.markus"), source);
    let mut program = parser::ast::Program::new(x);
    program.parse();

    println!("{:#?}", program.declarations);

    Ok(())
}
