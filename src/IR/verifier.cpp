#include "IR/verifier.hpp"

#include <assert.h>

#include "IR/query.hpp"
#include "diagnostics/controller.hpp"
#include "value/container.hpp"

namespace IR {

namespace Verify {
using namespace Diagnostics;
bool is(Query* query, Value::Call* call) {
  assert(call->getCalleeName() == "is");
  std::vector<Value::Container*> arguments = call->getArguments();

  if (arguments.size() != 1) {
    Controller::report(Error::wrongNumberOfArguments(1, call));
    return false;
  }

  if (!arguments[0]->isType()) {
    Controller::report(
        Error::wrongArgumentType(Value::VALUE_KIND_TYPE, arguments[0]));
    return false;
  }

  return true;
}
}  // namespace Verify

bool verifyCall(Query* query, Value::Call* call) {
  std::string functionName = call->getCalleeName();

  if (functionName == "is")
    return Verify::is(query, call);

  return false;
}
}  // namespace IR