mod common;
mod ir;
mod parser;
mod program;
use std::fs;

fn main() -> Result<(), Box<dyn std::error::Error + 'static>> {
    let filename = "x.markus";
    let raw = fs::read_to_string("x.markus")?;
    let source = parser::Source::new(filename, &raw);

    let mut program = program::Program::new(source);
    program.parse();
    program.verify();

    if !program.is_good() {
        eprintln!("{:#?}", program.diagnostics);
        return Ok(());
    }

    ir::typespace::IrTypeSpace::from_type_space(&program.type_space);

    Ok(())
}
