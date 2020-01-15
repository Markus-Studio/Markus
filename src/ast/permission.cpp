#include "ast/permission.hpp"

#include "ast/program.hpp"
#include "ast/query.hpp"

namespace AST {
Permission::Permission(Program* program, std::string name) {
  Type::Container* users = new Type::Container(program->unionOfUsers());
  query = new Query(program, users);
  this->name = name;
}

std::string Permission::getName() {
  return name;
}

Query* Permission::getQuery() {
  return query;
}
}  // namespace AST