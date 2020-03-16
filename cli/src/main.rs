mod cli;

fn main() {
    std::process::exit(match cli::Cli::new().run() {
        true => 0,
        false => -1,
    });
}
