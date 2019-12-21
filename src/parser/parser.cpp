#include "parser/parser.hpp"
#include "parser/scanner.hpp"
#include "parser/tokenizer.hpp"
#include "parser/types.hpp"
#include "IR/program.hpp"

namespace Parser {
IR::Program* createProgram(std::string code) {
  Parser::TokenVec tokens = Parser::tokenize(code);
  Parser::Scanner scanner(tokens);
  Parser::Types types(&scanner);
  return new IR::Program(&types);
}
}