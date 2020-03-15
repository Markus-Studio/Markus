mod cli;
mod common;
mod ir;
mod parser;
mod program;
mod verifier;

fn main() {
    std::process::exit(match cli::Cli::new().run() {
        true => 0,
        false => -1,
    });
}
