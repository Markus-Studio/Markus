#include "parser/permission.hpp"

#include <assert.h>

namespace Parser {
IR::Permission* parsePermission(IR::Program* program, TokenVec* tokens) {
  std::vector<Token*>::iterator iterator = tokens->begin();
  assert(**iterator == "permission");
}
}  // namespace Parser