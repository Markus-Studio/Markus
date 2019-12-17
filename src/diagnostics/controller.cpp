#include "diagnostics/controller.hpp"

#include <iostream>
#include <list>

#include "diagnostics/error.hpp"

namespace Diagnostics {
std::list<Error*> Controller::errors;

void Controller::report(Error* err) {
  errors.push_back(err);
}

bool Controller::hasError() {
  return !errors.empty();
}

void Controller::dumpAll() {
  if (!hasError())
    return;

  std::list<Error*>::iterator it;
  for (it = errors.begin(); it != errors.end(); ++it)
    std::cerr << (*it)->getMessage() << std::endl;
}
}  // namespace Diagnostics