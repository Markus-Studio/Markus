use std::fs;
mod ast;

fn main() -> Result<(), Box<dyn std::error::Error + 'static>> {
    let data = fs::read("x.markus")?;
    let source = String::from_utf8_lossy(&data).to_string();
    let x = ast::source::Source::new(String::from("x.markus"), &source);

    ast::tokenizer::Tokenizer::new(&x);

    Ok(())
}
