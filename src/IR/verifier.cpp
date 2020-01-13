#include "IR/verifier.hpp"

#include <assert.h>

#include "IR/query.hpp"
#include "diagnostics/controller.hpp"
#include "value/container.hpp"

namespace IR {
using namespace Diagnostics;

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

#define EXPECT_ARG_CURRENT(n)                                        \
  EXPECT_ARG_TYPE(n, Value::VALUE_KIND_VARIABLE);                    \
  if (arguments[n]->asVariable()->getId() != 0) {                    \
    Controller::report(                                              \
        Error::variableExpectedCurrent(arguments[n]->asVariable())); \
    return false;                                                    \
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

#define EXPECT_TYPE(check, type)                           \
  if (!(check)) {                                          \
    Controller::report(Error::wrongInputType(call, type)); \
    return false;                                          \
  }

namespace Verify {
bool is(Query* query, Value::Call* call, Type::Container*& resultType) {
  assert(call->getCalleeName() == "is");
  std::vector<Value::Container*> arguments = call->getArguments();

  EXPECT_ARG_NUM(1);
  EXPECT_ARG_TYPE(0, Value::VALUE_KIND_TYPE);
  resultType = resultType->extract(arguments[0]->asType()->getType());

  return true;
}

bool select(Query* query, Value::Call* call, Type::Container*& resultType) {
  assert(call->getCalleeName() == "select");
  std::vector<Value::Container*> arguments = call->getArguments();

  EXPECT_ARG_NUM(1);
  EXPECT_ARG_CURRENT(0);
  EXPECT_ARG_VAR_EXISTS(0);

  resultType = arguments[0]->asVariable()->getType();
  return true;
}

bool sum1(Query* query, Value::Call* call, Type::Container*& resultType) {
  assert(call->getCalleeName() == "sum");
  std::vector<Value::Container*> arguments = call->getArguments();

  EXPECT_ARG_NUM(1);
  EXPECT_ARG_CURRENT(0);
  EXPECT_ARG_VAR_EXISTS(0);

  Type::Container* type = arguments[0]->asVariable()->getType();

  EXPECT_TYPE_SHAPE(type, 1);

  type = type->asArray()->getContainedType();
  EXPECT_TYPE(IS_NUMBER(type), "number");
  resultType = type;
  return true;
}

}  // namespace Verify

bool verifyCall(Query* query, Value::Call* call, Type::Container*& resultType) {
  std::string functionName = call->getCalleeName();

  if (functionName == "is")
    return Verify::is(query, call, resultType);

  if (functionName == "select")
    return Verify::select(query, call, resultType);

  if (functionName == "sum" && call->numArguments() == 1)
    return Verify::sum1(query, call, resultType);

  Controller::report(Error::cannotResolveName(call));
  return false;
}
}  // namespace IR