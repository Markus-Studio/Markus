use std::fs;
use std::time::{Duration, Instant};
mod ast;

fn main() -> Result<(), Box<dyn std::error::Error + 'static>> {
    let data = fs::read("x.markus")?;
    let source = String::from_utf8_lossy(&data).to_string();
    let mut x = ast::source::Source::new(String::from("x.markus"), &source);

    let tokenizer = ast::tokenizer::Tokenizer::new(&mut x);

    let start = Instant::now();
    let tokens: Vec<ast::tokenizer::Token> = tokenizer.collect();
    let duration = start.elapsed();
    println!("Time elapsed in expensive_function() is: {:?}", duration);

    for token in tokens {
        // match token {
        //     ast::tokenizer::Token::LeftParenthesis => {
        //         println!("Token (");
        //     }
        //     ast::tokenizer::Token::RightParenthesis => {
        //         println!("Token )");
        //     }
        //     ast::tokenizer::Token::LeftBrace => {
        //         println!("Token {{");
        //     }
        //     ast::tokenizer::Token::RightBrace => {
        //         println!("Token }}");
        //     }
        //     ast::tokenizer::Token::Dot => {
        //         println!("Token .");
        //     }
        //     ast::tokenizer::Token::Comma => {
        //         println!("Token ,");
        //     }
        //     ast::tokenizer::Token::Semicolon => {
        //         println!("Token ;");
        //     }
        //     ast::tokenizer::Token::Colon => {
        //         println!("Token :");
        //     }
        //     ast::tokenizer::Token::At => {
        //         println!("Token @");
        //     }
        //     ast::tokenizer::Token::Identifier(id) => {
        //         println!("Token Identifier {}", id);
        //     }
        //     ast::tokenizer::Token::Parameter(id) => {
        //         println!("Token Parameter {}", id);
        //     }
        //     ast::tokenizer::Token::InternalVariable(id) => {
        //         println!("Token Internal {}", id);
        //     }
        //     ast::tokenizer::Token::Int(num) => {
        //         println!("Token Int {}", num);
        //     }
        //     ast::tokenizer::Token::Float(num) => {
        //         println!("Token Float {}", num);
        //     }
        // }
    }

    Ok(())
}
