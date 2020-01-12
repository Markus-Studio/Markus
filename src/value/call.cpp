#include "value/call.hpp"

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

}  // namespace Value
