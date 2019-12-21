#include "IR/permission.hpp"

#include "IR/query.hpp"

namespace IR {
Permission::Permission(Program* program, std::string name) {
  query = new Query(program, new Type::Container(program->unionOfUsers()));
  this->name = name;
}

std::string Permission::getName() {
  return name;
}

Query* Permission::getQuery() {
  return query;
}
}  // namespace IR