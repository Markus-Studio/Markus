#ifndef __MARKUS_TEST__
#define __MARKUS_TEST__

#include <iostream>
#include <list>
#include <string>

/**
 * A **very** simple testing framework for c++, I actually wanted to use catch2
 * but there were some compiler errors which I couldn't understand, so here we
 * are writing our own minimalist testing framework, also I hate that things
 * like catch2 have like 20K LOC.
 */
namespace MarkusTesting {
/**
 * This struct is passed to each test function so they can report
 * the current status of the running test.
 */
struct TestContext {
  /**
   * Description of the test, it's what will be printed on the screen.
   */
  std::string description;

  /**
   * The callback function that should be invoked in order to run the test.
   */
  void (*cb)(struct TestContext*);

  /**
   * Makes the test runner print the status of this test again.
   */
  void (*updated)(struct TestContext* current);

  /**
   * Whatever the current test has failed or not.
   */
  bool failed;

  /**
   * Whatever this test has finished execution or not.
   */
  bool finished;

  /**
   * Name of the current unit that we're runnning at this moment.
   */
  std::list<std::string> currentUnit;
};

/**
 * This struct helps us to auto register the tests.
 */
struct AutoReg {
  /**
   * When this constructor is called we create a new test and append it to
   * the registeredTests list.
   */
  AutoReg(std::string description, void (*cb)(struct TestContext*));
};

/**
 * Run the tests.
 */
int run();
}  // namespace MarkusTesting

#endif