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
    let time = now.elapsed().as_micros();

    // let v_now = Instant::now();
    // program.verify();
    // let v_time = v_now.elapsed().as_micros();

    println!("{:#?}", program.declarations);
    println!(">>> parsed in {} micro-sec", time);
    println!("Diagnostics:");
    println!("{:#?}", program.diagnostics);
    // println!(">>> verified in {} micro-sec", v_time);

    Ok(())
}
