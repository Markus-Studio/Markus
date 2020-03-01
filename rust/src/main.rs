mod common;
mod verifier;
mod ir;
mod parser;
mod program;
use std::fs;

fn main() -> Result<(), Box<dyn std::error::Error + 'static>> {
    let filename = "./x.markus";
    let raw = fs::read_to_string("x.markus")?;
    let source = parser::Source::new(filename, &raw);

    let mut program = program::Program::new(source);
    program.parse();
    program.verify();

    println!("{:#?}", program.declarations);

    if !program.is_good() {
        for diagnostic in &program.diagnostics {
            let uri = diagnostic.get_uri(&program.source);
            let msg = diagnostic.to_string();
            eprintln!("{} - {}", uri, msg);
        }
        return Ok(());
    }

    Ok(())
}
