#include "value/variable.hpp"

namespace Value {
Variable::Variable(int id, Type::Container type, Parser::Range range) {
  hasVariableMember = false;
  variableId = id;
  variableType = type;
  variableMember = new Type::Uri();
  this->range = range;
}

Variable::Variable(int id,
                   Type::Container type,
                   Parser::Range range,
                   Type::Uri* member) {
  hasVariableMember = !member->isEmpty();
  variableId = id;
  variableType = type;
  variableMember = member;
  this->range = range;
}

bool Variable::hasMember() {
  return hasVariableMember;
}

Type::Container Variable::getBaseType() {
  return variableType;
}

Type::Container Variable::getType() {
  if (!hasVariableMember)
    return variableType;
  return variableType.query(*variableMember);
}

Type::Uri* Variable::getMember() {
  return variableMember;
}

int Variable::getId() {
  return variableId;
}

Parser::Range Variable::getRange() {
  return range;
}
}  // namespace Value