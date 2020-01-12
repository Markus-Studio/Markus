#include "value/variable.hpp"

namespace Value {
Variable::Variable(int id, Type::Container* type) {
  hasVariableMember = false;
  variableId = id;
  variableType = type;
  variableMember = new Type::Uri();
  typeCache = NULL;
}

Variable::Variable(int id, Type::Container* type, Type::Uri* member) {
  hasVariableMember = !member->isEmpty();
  variableId = id;
  variableType = type;
  variableMember = member;
  typeCache = NULL;
}

bool Variable::hasMember() {
  return hasVariableMember;
}

Type::Container* Variable::getBaseType() {
  return variableType;
}

Type::Container* Variable::getType() {
  if (typeCache != NULL)
    return typeCache;
  if (!hasVariableMember)
    return typeCache = variableType;
  return typeCache = variableType->query(*variableMember);
}

Type::Uri* Variable::getMember() {
  return variableMember;
}
}  // namespace Value