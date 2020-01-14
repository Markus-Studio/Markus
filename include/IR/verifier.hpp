#ifndef __MARKUS_IR_VERIFIER__
#define __MARKUS_IR_VERIFIER__

#include "type/container.hpp"
#include "value/call.hpp"

#define EXPECT_ARG_TYPE(n, type)                                        \
  if (arguments[n]->getKind() != (type)) {                              \
    Controller::report(Error::wrongArgumentType((type), arguments[n])); \
    return false;                                                       \
  }

#define EXPECT_ARG_NUM(n)                                       \
  if (call->numArguments() != n) {                              \
    Controller::report(Error::wrongNumberOfArguments(n, call)); \
    return false;                                               \
  }

#define EXPECT_ARG_CURRENT(n)                                          \
  {                                                                    \
    EXPECT_ARG_TYPE(n, Value::VALUE_KIND_VARIABLE);                    \
    if (arguments[n]->asVariable()->getId() != 0) {                    \
      Controller::report(                                              \
          Error::variableExpectedCurrent(arguments[n]->asVariable())); \
      return false;                                                    \
    }                                                                  \
  }

#define EXPECT_ARG_VAR_EXISTS(n)                                               \
  if (arguments[n]->asVariable()->getType()->isNil()) {                        \
    Controller::report(Error::fieldDoesNotExists(arguments[n]->asVariable())); \
    return false;                                                              \
  }

#define EXPECT_TYPE_SHAPE(type, n)                                           \
  if ((type)->getShape() != n) {                                             \
    Controller::report(Error::wrongInputShape(call, n, (type)->getShape())); \
    return false;                                                            \
  }

#define IS_BUILTIN(container, type) \
  ((container)->is(query->getOwner()->resolveBuiltin(type)))

#define IS_NUMBER(container) \
  (IS_BUILTIN(container, "int") || IS_BUILTIN(container, "float"))

#define IS_FIELD(n) \
  (arguments[n]->isVariable() && arguments[n]->asVariable()->getId() == 0)

#define IS_VAR(n) \
  (arguments[n]->isVariable() && arguments[n]->asVariable()->getId() != 0)

#define IS_VAR_OR_FIELD(n) (arguments[n]->isVariable())

#define IS_LITERAL(n) (arguments[n]->isLiteral())

#define IS_TYPE_REF(n) (arguments[n]->isType())

#define EXPECT_TYPE(check, type)                           \
  if (!(check)) {                                          \
    Controller::report(Error::wrongInputType(call, type)); \
    return false;                                          \
  }

namespace IR {
class Query;

bool verifyCall(Query* query, Value::Call* call, Type::Container*& resultType);
}  // namespace IR

#endif