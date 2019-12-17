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
  static bool hadUnit = false;
  std::cout << "\r";

  switch (r) {
    case UR_STARTED:
      std::cout << "[      ] " << current->description;
      hadUnit = false;
      return;
    case UR_FAILED:
      if (current->currentUnit.size()) {
        std::cout << " FAILED->";
        std::cout << std::string(current->currentUnit.size() * 2 - 2, ' ');
        std::cout << current->currentUnit.back();
        std::cout << std::endl;
      }
      std::cout << std::string(50, '#') << std::endl;
      std::cout << "#  " << current->error << std::endl;
      std::cout << std::string(50, '#') << std::endl;
      std::cout << "[FAILED] " << current->description << std::endl;
      return;
    case UR_COMPLETED:
      if (current->failed)
        return;
      if (hadUnit)
        std::cout << std::endl;
      std::cout << "[  OK  ] " << current->description << std::endl;
      return;
    case UR_ENTER_UNIT:
      std::cout << std::endl;
      std::cout << "  UNIT ";
      std::cout << std::string(current->currentUnit.size() * 2, ' ');
      std::cout << current->currentUnit.back();
      hadUnit = true;
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
  MarkusTesting::run();
}