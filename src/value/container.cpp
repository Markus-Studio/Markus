#include "value/container.hpp"

#include <assert.h>

#include "ast/source.hpp"

namespace Value {
Container::Container() {
  value = NULL;
}

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

Container::Container(Call* v) {
  kind = VALUE_KIND_CALL;
  value = v;
}

Container::Container(TypeValue* v) {
  kind = VALUE_KIND_TYPE;
  value = v;
}

Container::Container(AST::Query* query) {
  kind = VALUE_KIND_QUERY;
  value = query;
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
  return kind == VALUE_KIND_INT || kind == VALUE_KIND_FLOAT ||
         kind == VALUE_KIND_BOOL || kind == VALUE_KIND_STRING;
}

bool Container::isVariable() {
  return kind == VALUE_KIND_VARIABLE;
}

bool Container::isCall() {
  return kind == VALUE_KIND_CALL;
}

bool Container::isType() {
  return kind == VALUE_KIND_TYPE;
}

bool Container::isQuery() {
  return kind == VALUE_KIND_QUERY;
}

bool Container::isField() {
  return kind == VALUE_KIND_VARIABLE && asVariable()->getId() == 0;
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

Call* Container::asCall() {
  assert(kind == VALUE_KIND_CALL);
  return (Call*)value;
}

TypeValue* Container::asType() {
  assert(kind == VALUE_KIND_TYPE);
  return (TypeValue*)value;
}

AST::Query* Container::asQuery() {
  assert(kind == VALUE_KIND_QUERY);
  return (AST::Query*)value;
}

enum ValueKind Container::getKind() {
  return kind;
}

Parser::Range Container::getRange() {
  switch (kind) {
    case VALUE_KIND_BOOL:
      return asBool()->getRange();
    case VALUE_KIND_INT:
      return asInt()->getRange();
    case VALUE_KIND_FLOAT:
      return asFloat()->getRange();
    case VALUE_KIND_STRING:
      return asString()->getRange();
    case VALUE_KIND_TYPE:
      return asType()->getRange();
    case VALUE_KIND_VARIABLE:
      return asVariable()->getRange();
    case VALUE_KIND_CALL:
      return asCall()->getRange();
    case VALUE_KIND_QUERY:
      // TODO(qti3e)
      return Parser::Range();
  }
}

Type::Container Container::getType(AST::Query* query) {
  switch (kind) {
    case VALUE_KIND_BOOL:
      return query->getOwner()->resolveBuiltin("bool");
    case VALUE_KIND_INT:
      return query->getOwner()->resolveBuiltin("int");
    case VALUE_KIND_FLOAT:
      return query->getOwner()->resolveBuiltin("float");
    case VALUE_KIND_STRING:
      return query->getOwner()->resolveBuiltin("string");
    case VALUE_KIND_TYPE:
      return asType()->getType();
    case VALUE_KIND_VARIABLE:
      return asVariable()->getType();
    case VALUE_KIND_QUERY:
      return asQuery()->getResultType();
    case VALUE_KIND_CALL:
      return Type::Container();  // TODO(qti3e)
  }
}
}  // namespace Value