#include "IR/permission.hpp"

#include <iostream>

#include "IR/query.hpp"

namespace IR {
Permission::Permission(Program* program, std::string name) {
  Type::Container* users = new Type::Container(program->unionOfUsers());
  query = new Query(program, users);
  this->name = name;
  std::cout << "P" << users->isNil() << std::endl;
}

std::string Permission::getName() {
  return name;
}

Query* Permission::getQuery() {
  return query;
}
}  // namespace IR