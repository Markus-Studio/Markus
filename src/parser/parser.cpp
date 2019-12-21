#include "parser/parser.hpp"

namespace Parser {
IR::Program* createProgram(std::string code) {
  Parser::TokenVec tokens = Parser::tokenize(code);
  Parser::Scanner scanner(tokens);
  Parser::Types types(&scanner);
  return new IR::Program(&types);
}
}  // namespace Parser