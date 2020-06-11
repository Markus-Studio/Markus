extern crate clap;
use clap::{App, Arg, ArgMatches, SubCommand};
use frontend::source::Source;
use std::fs;

pub struct Cli {
    source: Option<Source>,
}

impl Cli {
    fn build_app() -> clap::App<'static, 'static> {
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

    fn completion(matches: &ArgMatches) -> bool {
        let shell: clap::Shell = match matches.subcommand() {
            ("bash", _) => clap::Shell::Bash,
            ("fish", _) => clap::Shell::Fish,
            ("zsh", _) => clap::Shell::Zsh,
            ("powershell", _) => clap::Shell::PowerShell,
            ("Elvish", _) => clap::Shell::Elvish,
            _ => {
                eprintln!("{}", matches.usage());
                eprintln!("Use --help for more info.");
                return false;
            }
        };

        Cli::build_app().gen_completions_to("markus", shell, &mut std::io::stdout());

        true
    }

    fn open_source_file(
        &mut self,
        filename: String,
    ) -> Result<(), Box<dyn std::error::Error + 'static>> {
        let raw = fs::read_to_string(filename.to_owned())?;
        self.source = Some(Source::new(&filename, &raw));
        Ok(())
    }

    fn open_input(&mut self, matches: &ArgMatches) -> bool {
        let filename = matches.value_of("INPUT").unwrap().to_string();
        if let Err(e) = self.open_source_file(filename) {
            eprintln!("error: {}", e);
            false
        } else {
            true
        }
    }

    fn ast(&mut self) -> bool {
        self.source.as_mut().unwrap().ast();
        false
    }

    fn check(&mut self, matches: &ArgMatches) -> bool {
        // let silent = matches.is_present("silent");
        // let program = self.program.as_mut().unwrap();
        // program.parse();
        // program.verify();

        // if silent {
        //     return program.is_good();
        // }

        // if program.is_good() {
        //     println!("Verified program successfully.");
        // } else {
        //     for diagnostic in &program.diagnostics {
        //         let uri = diagnostic.get_uri(&program.source);
        //         let msg = diagnostic.to_string();
        //         println!("{} - {}", uri, msg);
        //     }
        // }

        // program.is_good()
        unimplemented!()
    }

    fn gen(&mut self, _matches: &ArgMatches) -> bool {
        // let program = self.program.as_mut().unwrap();
        // generate_ir(&program.declarations);
        true
    }

    pub fn new() -> Cli {
        Cli { source: None }
    }

    pub fn run(&mut self) -> bool {
        let app_matches = Cli::build_app().get_matches();
        match app_matches.subcommand() {
            ("completion", Some(sub)) => Cli::completion(sub),

            ("ast", Some(matches)) => self.open_input(matches) && self.ast(),
            ("check", Some(matches)) => self.open_input(matches) && self.check(matches),
            ("gen", Some(matches)) => {
                self.open_input(matches) && self.check(matches) && self.gen(matches)
            }

            _ => {
                eprintln!("{}", app_matches.usage());
                eprintln!("Use --help for more info.");
                false
            }
        }
    }
}
