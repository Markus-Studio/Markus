#ifndef __MARKUS_IR_VERIFIER__
#define __MARKUS_IR_VERIFIER__

#include <string>

#include "IR/program.hpp"
#include "IR/query.hpp"
#include "diagnostics/controller.hpp"
#include "type/container.hpp"
#include "value/call.hpp"

namespace Verifier {
/**
 * A pipline.
 */
struct Pipeline {
  /**
   * The callback function that is used to verify the pipeline.
   */
  bool (*cb)(IR::Query*, std::vector<Value::Container*>, Type::Container*&);

  /**
   * Number of arguments that must be passed to the callback.
   */
  int numArgs;

  /**
   * Name of the pipeline.
   */
  std::string name;
};

/**
 * This struct helps us to auto register the pipelines.
 */
struct PipelineAutoReg {
  PipelineAutoReg(std::string name,
                  int numArgs,
                  bool (*cb)(IR::Query*,
                             std::vector<Value::Container*>,
                             Type::Container*&));
};

/**
 * Verify a pipeline.
 */
bool verifyCall(IR::Query* query,
                Value::Call* call,
                Type::Container*& resultType);
}  // namespace Verifier

// ---- MACROS ----

#define MARKUS_CONCAT2(a, b) a##b
#define MARKUS_CONCAT(a, b) MARKUS_CONCAT2(a, b)

#define MARKUS_PIPELINE2(FN_NAME, REG_NAME, NAME, NUM_ARGS)                \
  bool FN_NAME(IR::Query* query, std::vector<Value::Container*> arguments, \
               Type::Container*& resultType);                              \
                                                                           \
  namespace {                                                              \
  Verifier::PipelineAutoReg REG_NAME(#NAME, NUM_ARGS, &FN_NAME);           \
  }                                                                        \
                                                                           \
  bool FN_NAME(IR::Query* query, std::vector<Value::Container*> arguments, \
               Type::Container*& resultType)

#define MARKUS_PIPELINE3(FN_NAME, NAME, NUM_ARGS)                           \
  MARKUS_PIPELINE2(FN_NAME, MARKUS_CONCAT(pipelineAutoReg_, FN_NAME), NAME, \
                   NUM_ARGS)

#define MARKUS_PIPELINE(name, numArgs) \
  MARKUS_PIPELINE3(MARKUS_CONCAT(name, numArgs), name, numArgs)

#define EXPECT_ARG_KIND(n, kind)                                      \
  if (arguments[n]->getKind() != (kind)) {                            \
    Diagnostics::Controller::report(                                  \
        Diagnostics::Error::wrongArgumentType((kind), arguments[n])); \
    return false;                                                     \
  }

#define EXPECT_ARG_FIELD(n)                            \
  {                                                    \
    EXPECT_ARG_KIND(n, Value::VALUE_KIND_VARIABLE);    \
    if (arguments[n]->asVariable()->getId() != 0) {    \
      Diagnostics::Controller::report(                 \
          Diagnostics::Error::variableExpectedCurrent( \
              arguments[n]->asVariable()));            \
      return false;                                    \
    }                                                  \
  }

#define EXPECT_ARG_FIELD_EXISTS(n)                                           \
  if (arguments[n]->asVariable()->getType()->isNil()) {                      \
    Diagnostics::Controller::report(                                         \
        Diagnostics::Error::fieldDoesNotExists(arguments[n]->asVariable())); \
    return false;                                                            \
  }

#endif