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
  if (arguments.size() != n) {                                  \
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

}  // namespace Verify

bool verifyCall(Query* query, Value::Call* call, Type::Container*& resultType) {
  std::string functionName = call->getCalleeName();

  resultType->dump();

  if (functionName == "is")
    return Verify::is(query, call, resultType);

  if (functionName == "select")
    return Verify::select(query, call, resultType);

  Controller::report(Error::cannotResolveName(call));
  return false;
}
}  // namespace IR