mod common;
mod ir;
mod parser;
mod program;
mod verifier;

extern crate clap;
use clap::{App, Arg, ArgMatches, SubCommand};
use std::fs;

fn build_cli() -> clap::App<'static, 'static> {
    App::new("Markus")
        .version("0.0.1")
        .author("Parsa G. <qti3eqti3e@gmail.com>")
        .about("Markus Language Toolchain & Compiler")
        .subcommands(vec![
            SubCommand::with_name("gen")
                .about("Build the source file.")
                .arg(
                    Arg::with_name("INPUT")
                        .help("Sets the input file to use.")
                        .required(true),
                ),
            SubCommand::with_name("check")
                .about("Validates the program.")
                .arg(
                    Arg::with_name("silent")
                        .short("s")
                        .long("silent")
                        .help("Fails silently without printing diagnostic messages."),
                )
                .arg(
                    Arg::with_name("INPUT")
                        .help("Sets the input file to use.")
                        .required(true),
                ),
            SubCommand::with_name("ast")
                .about("Prints the AST of the source file.")
                .arg(
                    Arg::with_name("INPUT")
                        .help("Sets the input file to use.")
                        .required(true),
                ),
            SubCommand::with_name("completion")
                .about("Generate completion for your shell.")
                .subcommands(vec![
                    SubCommand::with_name("bash").about("Generates a .bash completion file for the Bourne Again SHell (BASH)"),
                    SubCommand::with_name("fish").about("Generates a .fish completion file for the Friendly Interactive SHell (fish)"),
                    SubCommand::with_name("zsh").about("Generates a completion file for the Z SHell (ZSH)"),
                    SubCommand::with_name("powershell").about("Generates a completion file for PowerShell"),
                    SubCommand::with_name("elvish").about("Generates a completion file for Elvish"),
                ])
        ])
}

fn command_gen(matches: &ArgMatches) -> Result<bool, Box<dyn std::error::Error + 'static>> {
    let silent = matches.is_present("silent");
    let filename = matches.value_of("INPUT").unwrap();
    let raw = fs::read_to_string(filename)?;
    let source = parser::Source::new(filename, &raw);

    let mut program = program::Program::new(source);
    program.parse();
    program.verify();

    if !program.is_good() {
        if !silent {
            for diagnostic in &program.diagnostics {
                let uri = diagnostic.get_uri(&program.source);
                let msg = diagnostic.to_string();
                println!("{} - {}", uri, msg);
            }
        }

        return Ok(false);
    }

    program::gen(program.declarations);

    Ok(true)
}

fn command_check(matches: &ArgMatches) -> Result<bool, Box<dyn std::error::Error + 'static>> {
    let silent = matches.is_present("silent");
    let filename = matches.value_of("INPUT").unwrap();
    let raw = fs::read_to_string(filename)?;
    let source = parser::Source::new(filename, &raw);

    let mut program = program::Program::new(source);
    program.parse();
    program.verify();

    if !program.is_good() {
        if !silent {
            for diagnostic in &program.diagnostics {
                let uri = diagnostic.get_uri(&program.source);
                let msg = diagnostic.to_string();
                println!("{} - {}", uri, msg);
            }
        }

        return Ok(false);
    } else if !silent {
        println!("Verified program successfully.");
    }

    Ok(true)
}

fn command_print_ast(matches: &ArgMatches) -> Result<bool, Box<dyn std::error::Error + 'static>> {
    let filename = matches.value_of("INPUT").unwrap();
    let raw = fs::read_to_string(filename)?;
    let source = parser::Source::new(filename, &raw);

    let mut program = program::Program::new(source);
    program.parse();

    println!("{:#?}", program.declarations);

    Ok(true)
}

fn run_app(matches: &ArgMatches) -> Result<bool, Box<dyn std::error::Error + 'static>> {
    match matches.subcommand() {
        ("gen", Some(sub)) => command_gen(sub),
        ("check", Some(sub)) => command_check(sub),
        ("ast", Some(sub)) => command_print_ast(sub),
        ("completion", Some(sub)) => {
            let shell: clap::Shell = match sub.subcommand() {
                ("bash", _) => clap::Shell::Bash,
                ("fish", _) => clap::Shell::Fish,
                ("zsh", _) => clap::Shell::Zsh,
                ("powershell", _) => clap::Shell::PowerShell,
                ("Elvish", _) => clap::Shell::Elvish,
                _ => {
                    eprintln!("{}", sub.usage());
                    eprintln!("Use --help for more info.");
                    return Ok(false);
                }
            };

            build_cli().gen_completions_to("markus", shell, &mut std::io::stdout());

            Ok(true)
        }
        _ => {
            eprintln!("{}", matches.usage());
            eprintln!("Use --help for more info.");
            Ok(false)
        }
    }
}

fn main() {
    let matches = build_cli().get_matches();

    std::process::exit(match run_app(&matches) {
        Ok(true) => 0,
        Ok(false) => -1,
        Err(err) => {
            eprintln!("error: {}", err);
            -1
        }
    });
}
