mod parser;
mod program;
use std::fs;
use std::time::Instant;

fn main() -> Result<(), Box<dyn std::error::Error + 'static>> {
    let filename = "x.markus";
    let raw = fs::read_to_string("x.markus")?;
    let source = parser::Source::new(filename, &raw);

    let mut program = program::Program::new(source);

    let now = Instant::now();
    program.parse();
    println!("{}", now.elapsed().as_micros());

    Ok(())
}
