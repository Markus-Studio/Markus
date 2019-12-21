#include "parser/parser.hpp"

namespace Parser {
IR::Program* createProgram(std::string code) {
  Parser::TokenVec tokens = Parser::tokenize(code);
  Parser::Scanner scanner(tokens);
  return new IR::Program(&scanner);
}
}  // namespace Parser