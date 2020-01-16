#include "ast/permission.hpp"

#include "ast/query.hpp"
#include "ast/source.hpp"

namespace AST {
Permission::Permission(Source* program, std::string name) {
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