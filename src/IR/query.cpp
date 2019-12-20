#include "IR/query.hpp"

namespace IR {
Query::Query(Program* program) {
  owner = program;
  resultType = new Type::Container(program->arrayOfTypes());
}

Query::Query(Program* program, Type::Container* type) {
  owner = program;
  resultType = type;
}

int Query::addParameter(Type::Container* type) {
  parameters.push_back(type);
  return parameters.size() - 1;
}

Type::Container* Query::getParameterType(int n) {
  return parameters[n];
}

// Filter builder implementation.

bool Query::is(std::string name) {}

}  // namespace IR