#include "value/call.hpp"

#include <assert.h>

namespace Value {
Call::Call(std::string calleeName) {
  functionName = calleeName;
}

Call::Call(Parser::Token* token) {
  assert(token->isIdentifier());
  functionName = token->getWord();
  range = *Parser::Range::fromToken(token);
}

void Call::addArgument(Container* value) {
  arguments.push_back(value);
}

std::string Call::getCalleeName() {
  return functionName;
}

std::vector<Container*> Call::getArguments() {
  std::vector<Container*> vec;
  vec.assign(arguments.begin(), arguments.end());
  vec.shrink_to_fit();
  return vec;
}

int Call::numArguments() {
  return arguments.size();
}

void Call::expandRange(Parser::Range r) {
  range = range + r;
}

Parser::Range Call::getRange() {
  return range;
}
}  // namespace Value
