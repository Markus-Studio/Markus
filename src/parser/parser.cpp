#include "parser/parser.hpp"

#include "diagnostics/controller.hpp"

namespace Parser {
IR::Program* createProgram(std::string code) {
  Parser::TokenVec tokens = Parser::tokenize(code);

  if (Diagnostics::Controller::hasError())
    return NULL;

  Parser::Scanner scanner(tokens);

  if (Diagnostics::Controller::hasError())
    return NULL;

  return new IR::Program(&scanner);
}
}  // namespace Parser