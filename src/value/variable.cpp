#include "value/variable.hpp"

namespace Value {
Variable::Variable(int id, Type::Container* type) {
  hasVariableMember = false;
  variableId = id;
  variableType = type;
  variableMember = new Type::Uri();
}

Variable::Variable(int id, Type::Container* type, Type::Uri* member) {
  hasVariableMember = true;
  variableId = id;
  variableType = type;
  variableMember = member;
}

bool Variable::hasMember() {
  return hasVariableMember;
}

Type::Container* Variable::getBaseType() {
  return variableType;
}

Type::Container* Variable::getType() {
  // TODO(qti3e)
  return variableType;
}

Type::Uri* Variable::getMember() {
  return variableMember;
}
}  // namespace Value