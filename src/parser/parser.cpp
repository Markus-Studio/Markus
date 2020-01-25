#include "parser/parser.hpp"

#include "diagnostics/controller.hpp"

namespace Parser {
AST::Source* createProgram(std::string code) {
  Parser::TokenVec tokens = Parser::tokenize(code);

  if (Diagnostics::Controller::hasError())
    return nullptr;

  Parser::Scanner scanner(tokens);

  if (Diagnostics::Controller::hasError())
    return nullptr;

  return new AST::Source(&scanner);
}
}  // namespace Parser