extern crate markus;
use markus::parser::tokenizer::*;

#[test]
fn basic() {
    let source = "query x { }";
    let data: Vec<u16> = source.encode_utf16().collect();
    let tokens: Vec<Token> = Tokenizer::new(&data, 0).collect();
    assert_eq!(tokens.len(), 4);
    assert!(tokens[0].is_identifer());
    assert!(!tokens[2].is_identifer());
    assert!(tokens[0].compare_identifier(&data, "query"));
    assert!(!tokens[0].compare_identifier(&data, "Hello World"));
    assert!(tokens[1].compare_identifier(&data, "x"));
}
