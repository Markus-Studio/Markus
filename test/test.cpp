#include "test.hpp"

namespace MarkusTesting {
/**
 * List of registred tests.
 */
std::list<struct TestContext*> registeredTests;

AutoReg::AutoReg(std::string description, void (*cb)(struct TestContext*)) {
  struct TestContext* test = new TestContext();
  test->description = description;
  test->cb = cb;
  test->finished = test->failed = false;
  registeredTests.push_back(test);
}

void printStatus(struct TestContext* current) {
  std::list<struct TestContext*>::iterator it = registeredTests.begin();
  std::cout << "\r";

  if (current->finished) {
    std::cout << (current->failed ? "[FAILED] " : "[  OK  ] ");
    std::cout << current->description << std::endl;
    return;
  }

  std::cout << (current->failed ? "[FAILED] " : "[      ] ");
  std::cout << current->description;
}

int run() {
  bool failed = false;
  std::list<struct TestContext*>::iterator it = registeredTests.begin();

  if (it == registeredTests.end()) {
    std::cerr << "Markus Testing Error: No tests." << std::endl;
    return -1;
  }

  std::cout << "Running " << registeredTests.size() << " tests:" << std::endl;

  for (; it != registeredTests.end(); ++it) {
    (*it)->updated = &printStatus;
    printStatus(*it);
    (*it)->cb(*it);
    (*it)->finished = true;
    printStatus(*it);
    if ((*it)->failed)
      failed = true;
  }

  return failed ? -1 : 0;
}
}  // namespace MarkusTesting

int main() {
  MarkusTesting::run();
}