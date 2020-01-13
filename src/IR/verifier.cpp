#include "IR/verifier.hpp"

#include <assert.h>

#include "IR/query.hpp"
#include "diagnostics/controller.hpp"
#include "value/container.hpp"

namespace IR {
using namespace Diagnostics;

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

bool sum0(Query* query, Value::Call* call, Type::Container*& resultType) {
  assert(call->getCalleeName() == "sum");
  EXPECT_ARG_NUM(0);
  EXPECT_TYPE_SHAPE(resultType, 1);
  EXPECT_TYPE(IS_NUMBER(resultType->asArray()->getContainedType()), "number");
  resultType = resultType->asArray()->getContainedType();
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

  if (functionName == "sum")
    return (call->numArguments() == 1) ? Verify::sum1(query, call, resultType)
                                       : Verify::sum0(query, call, resultType);

  Controller::report(Error::cannotResolveName(call));
  return false;
}
}  // namespace IR