#ifndef __MARKUS_TEST__
#define __MARKUS_TEST__

#include <stdio.h>

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
 * Passed to the ctx->updated(), tells the kind of update.
 */
enum UpdateReason {
  UR_STARTED,
  UR_FAILED,
  UR_ENTER_UNIT,
  UR_EXIT_UNIT,
  UR_COMPLETED,
  UR_ASSERT
};

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
  void (*updated)(struct TestContext* current, enum UpdateReason);

  /**
   * Whatever the current test has failed or not.
   */
  bool failed;

  /**
   * Whatever this test has finished execution or not.
   */
  bool finished;

  /**
   * Error message.
   */
  char error[512];
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

#define CHECK(e)                                                       \
  do {                                                                 \
    if (!(e)) {                                                        \
      ctx->failed = true;                                              \
      sprintf(ctx->error, "%s:%d\n\tFailed assertion `%s`.", __FILE__, \
              __LINE__, #e);                                           \
      ctx->updated(ctx, MarkusTesting::UR_FAILED);                     \
      return;                                                          \
    }                                                                  \
    ctx->updated(ctx, MarkusTesting::UR_ASSERT);                       \
  } while (0)

#define CHECK_TRUE(e) CHECK(e == true)
#define CHECK_FALSE(e) CHECK(e == true)

#define MARKUS_TESTING_CONCAT2(a, b) a##b
#define MARKUS_TESTING_CONCAT(a, b) MARKUS_TESTING_CONCAT2(a, b)
#define MARKUS_TESTING_UNIQUE_NAME(name) \
  MARKUS_TESTING_CONCAT(name, __COUNTER__)
#define MARKUS_TESTING_GET_TEST_NAME() MARKUS_TESTING_UNIQUE_NAME(MARKUS_test_)

#define MARKUS_TESTING_GENERATE_TEST(description, name)                    \
  void name(MarkusTesting::TestContext*);                                  \
  namespace {                                                              \
  MarkusTesting::AutoReg MARKUS_TESTING_UNIQUE_NAME(MAR_AUTO)(description, \
                                                              &name);      \
  }                                                                        \
  void name(MarkusTesting::TestContext* ctx)

#define TEST(description) \
  MARKUS_TESTING_GENERATE_TEST(description, MARKUS_TESTING_GET_TEST_NAME())

#endif