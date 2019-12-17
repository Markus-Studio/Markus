#include "test.hpp"

namespace MarkusTesting {
// List of registred tests.
std::list<struct TestContext*> registeredTests;

AutoReg::AutoReg(std::string description, void (*cb)(struct TestContext*)) {
  struct TestContext* test = new TestContext();
  test->description = description;
  test->cb = cb;
  test->finished = test->failed = false;
  registeredTests.push_back(test);
}

void printStatus(struct TestContext* current, enum UpdateReason r) {
  std::cout << "\r";

  switch (r) {
    case UR_STARTED:
      std::cout << "[      ] " << current->description;
      return;
    case UR_FAILED:
      std::cout << "[FAILED] " << current->description << std::endl;
      std::cout << std::string(80, '-') << std::endl;
      std::cout << current->error << std::endl;
      std::cout << std::string(80, '-') << std::endl;
      return;
    case UR_COMPLETED:
      if (current->failed)
        return;
      std::cout << "[  OK  ] " << current->description << std::endl;
      return;
    default:;
  }
}

int run() {
  bool failed = false;
  std::list<struct TestContext*>::iterator it = registeredTests.begin();
  std::cout << "Running " << registeredTests.size() << " tests:" << std::endl;

  for (; it != registeredTests.end(); ++it) {
    (*it)->updated = &printStatus;
    printStatus(*it, UR_STARTED);
    (*it)->cb(*it);
    (*it)->finished = true;
    printStatus(*it, UR_COMPLETED);
    if ((*it)->failed)
      failed = true;
  }

  return failed ? -1 : 0;
}
}  // namespace MarkusTesting

int main() {
  return MarkusTesting::run();
}