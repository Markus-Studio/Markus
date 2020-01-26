#include "ir/filter.hpp"

#include <assert.h>

#include <iostream>
#include <sstream>

namespace IR {
Filter::Filter() {}

Filter Filter::Binary(Value::Call* call) {
  Filter filter;
  filter._isBinary = true;

  std::string name = call->getCalleeName();
  std::vector<Value::Container> arguments = call->getArguments();
  int field;

  if (arguments.size() != 2)
    goto error;

  if (arguments[0].isField()) {
    field = 0;
    filter.field = *arguments[0].asVariable()->getMember();
    filter.value = arguments[1];
  } else if (arguments[1].isField()) {
    field = 1;
    filter.field = *arguments[1].asVariable()->getMember();
    filter.value = arguments[0];
  } else {
    goto error;
  }

  if (name == "eq") {
    filter.op = FILTER_EQ;
    return filter;
  }

  if (name == "neq") {
    filter.op = FILTER_NEQ;
    return filter;
  }

  if (name == "lt") {
    filter.op = field == 0 ? FILTER_LT : FILTER_GT;
    return filter;
  }

  if (name == "gt") {
    filter.op = field == 0 ? FILTER_GT : FILTER_LT;
    return filter;
  }

  if (name == "lte") {
    filter.op = field == 0 ? FILTER_LTE : FILTER_GTE;
    return filter;
  }

  if (name == "gte") {
    filter.op = field == 0 ? FILTER_GTE : FILTER_LTE;
    return filter;
  }

error:
  std::cerr << "Cannot create a binary filter from a call to " << name
            << std::endl;
  abort();
  return filter;
}

Filter Filter::Unary(Value::Call* call) {
  Filter filter;
  filter._isBinary = false;

  std::string name = call->getCalleeName();
  std::vector<Value::Container> arguments = call->getArguments();

  if (arguments.size() != 1)
    goto error;

  filter.value = arguments[0];

  if (name == "is") {
    filter.op = FILTER_IS;
    return filter;
  }

error:
  std::cerr << "Cannot create a unary filter from a call to " << name
            << std::endl;
  abort();
  return filter;
}

void Filter::applySelected(Filter& filter, Type::Uri selected) {
  if (selected.isEmpty())
    return;
  filter.field = filter.field.prepend(selected);
  // TODO(qti3e) Apply selected to the value.
}

Type::Uri Filter::getField() {
  assert(_isBinary == true);
  return field;
}

Value::Container Filter::getValue() {
  return value;
}

enum FilterOperator Filter::getOperator() {
  return op;
}

bool Filter::isStatic() {
  if (!value.isVariable())
    return true;
  return value.asVariable()->getId() == 0;
}

bool Filter::isBinary() {
  return _isBinary;
}

bool Filter::isEffecting(Type::Uri uri) {
  assert(_isBinary == true);
  std::vector<std::string> u1, u2;
  u1 = uri.getUnits();
  u2 = field.getUnits();

  int size = u1.size() < u2.size() ? u1.size() : u2.size();
  for (int i = 0; i < size; ++i)
    if (u1[i] != u2[i])
      return false;
  return true;
}

std::string Filter::toString() {
  std::stringstream stream;
  switch (op) {
    case FILTER_IS:
      stream << "is";
      break;
    case FILTER_EQ:
      stream << "eq";
      break;
    case FILTER_NEQ:
      stream << "neq";
      break;
    case FILTER_LT:
      stream << "lt";
      break;
    case FILTER_GT:
      stream << "gt";
      break;
    case FILTER_LTE:
      stream << "lte";
      break;
    case FILTER_GTE:
      stream << "gte";
      break;
  }

  stream << " ";
  if (_isBinary)
    stream << field.toString() << " ";

  switch (value.getKind()) {
    case Value::VALUE_KIND_NO_VALUE:
      stream << "[NIL]";
      break;
    case Value::VALUE_KIND_INT:
      stream << value.asInt()->getValue();
      break;
    case Value::VALUE_KIND_FLOAT:
      stream << value.asFloat()->getValue();
      break;
    case Value::VALUE_KIND_BOOL:
      stream << (value.asBool()->getValue() ? "true" : "false");
      break;
    case Value::VALUE_KIND_STRING:
      stream << value.asString()->getValue();
      break;
    case Value::VALUE_KIND_TYPE:
      stream << value.asType()->getType().toString();
      break;
    case Value::VALUE_KIND_QUERY:
      stream << "{QUERY}";
      break;
    case Value::VALUE_KIND_VARIABLE:
      stream << value.asVariable()->getId()
             << value.asVariable()->getMember()->toString();
      break;
    case Value::VALUE_KIND_CALL:
      stream << value.asCall()->getCalleeName() << "(...)";
      break;
  }

  return stream.str();
}

bool Filter::operator==(Filter rhs) {
  if (this->_isBinary != rhs._isBinary)
    return false;
  if (_isBinary)
    return this->op == rhs.op && this->field == rhs.field &&
           (const Value::Container)this->value ==
               (const Value::Container)rhs.value;
  return this->op == rhs.op && (const Value::Container)this->value ==
                                   (const Value::Container)rhs.value;
}
}  // namespace IR