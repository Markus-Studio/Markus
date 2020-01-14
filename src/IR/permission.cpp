#include "IR/permission.hpp"

#include "IR/program.hpp"
#include "IR/query.hpp"

namespace IR {
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
}  // namespace IR