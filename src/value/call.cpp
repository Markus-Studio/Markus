#include "value/call.hpp"

#include <assert.h>

#include "diagnostics/controller.hpp"

namespace Value {
Call::Call(std::string calleeName) {
  functionName = calleeName;
}

void Call::addArgument(Container* value) {
  arguments.push_back(value);
}

std::string Call::getCalleeName() {
  return functionName;
}

std::vector<Container*> Call::getArguments() {
  std::vector<Container*> vec;
  vec.assign(arguments.begin(), arguments.end());
  vec.shrink_to_fit();
  return vec;
}

namespace Verify {
using namespace Diagnostics;
bool is(Call* call, IR::Query* query) {
  assert(call->getCalleeName() == "is");
  std::vector<Container*> arguments = call->getArguments();

  if (arguments.size() != 1) {
    Controller::report(Error::wrongNumberOfArguments(1, arguments.size()));
    return false;
  }

  return true;
}
}  // namespace Verify

bool Call::verify(IR::Query* query) {
  if (functionName == "is")
    return Verify::is(this, query);

  return false;
}

Type::Container Call::getReturnType() {}
}  // namespace Value
