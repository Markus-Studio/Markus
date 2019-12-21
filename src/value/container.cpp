#include "value/container.hpp"

#include <assert.h>

namespace Value {
Container::Container(Int* v) {
  kind = VALUE_KIND_INT;
  value = v;
}

Container::Container(Float* v) {
  kind = VALUE_KIND_FLOAT;
  value = v;
}

Container::Container(Bool* v) {
  kind = VALUE_KIND_BOOL;
  value = v;
}

Container::Container(String* v) {
  kind = VALUE_KIND_STRING;
  value = v;
}

Container::Container(Variable* v) {
  kind = VALUE_KIND_VARIABLE;
  value = v;
}

bool Container::isInt() {
  return kind == VALUE_KIND_INT;
}

bool Container::isFloat() {
  return kind == VALUE_KIND_FLOAT;
}

bool Container::isNumericLiteral() {
  return kind == VALUE_KIND_INT || kind == VALUE_KIND_FLOAT;
}

bool Container::isBool() {
  return kind == VALUE_KIND_BOOL;
}

bool Container::isString() {
  return kind == VALUE_KIND_STRING;
}

bool Container::isLiteral() {
  return kind != VALUE_KIND_VARIABLE;
}

bool Container::isVariable() {
  return kind == VALUE_KIND_VARIABLE;
}

Int* Container::asInt() {
  assert(kind == VALUE_KIND_INT);
  return (Int*)value;
}

Float* Container::asFloat() {
  assert(kind == VALUE_KIND_FLOAT);
  return (Float*)value;
}

Bool* Container::asBool() {
  assert(kind == VALUE_KIND_BOOL);
  return (Bool*)value;
}

String* Container::asString() {
  assert(kind == VALUE_KIND_STRING);
  return (String*)value;
}

Variable* Container::asVariable() {
  assert(kind == VALUE_KIND_VARIABLE);
  return (Variable*)value;
}
}  // namespace Value