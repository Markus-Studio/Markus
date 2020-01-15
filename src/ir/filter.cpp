#include "ir/filter.hpp"

#include <iostream>

namespace IR {
Filter::Filter() {}

Filter Filter::Binary(Value::Call* call) {
  Filter filter;
  filter._isBinary = true;

  std::string name = call->getCalleeName();
  std::vector<Value::Container*> arguments = call->getArguments();
  int field;

  if (arguments.size() != 2)
    goto error;

  if (arguments[0]->isField()) {
    field = 0;
    filter.field = *arguments[0]->asVariable()->getMember();
    filter.value = *arguments[1];
  } else if (arguments[1]->isField()) {
    field = 1;
    filter.field = *arguments[1]->asVariable()->getMember();
    filter.value = *arguments[0];
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
  std::vector<Value::Container*> arguments = call->getArguments();

  if (arguments.size() != 1)
    goto error;

  filter.value = *arguments[0];

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

}  // namespace IR