#include "parser/permission.hpp"

#include <assert.h>

#include "diagnostics/controller.hpp"
#include "parser/query.hpp"

namespace Parser {
IR::Permission* parsePermission(IR::Program* program, TokenVec* tokens) {
  std::vector<Token*>::iterator iterator = tokens->begin();
  assert(**iterator == "permission");

  ++iterator;

  if (!(*iterator)->isIdentifier()) {
    Diagnostics::Controller::report(
        Diagnostics::Error::unexpectedToken(*iterator, "an identifier"));
    return NULL;
  }

  std::string name = (*iterator++)->getWord();
  IR::Permission* result = new IR::Permission(program, name);

  parseQuery(result->getQuery(), iterator);

  return result;
}
}  // namespace Parser