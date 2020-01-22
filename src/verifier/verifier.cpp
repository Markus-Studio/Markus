#include "verifier/verifier.hpp"

#include <assert.h>

#include <list>

#include "pipelines/eq.cpp"
#include "pipelines/groupBy.cpp"
#include "pipelines/is.cpp"
#include "pipelines/select.cpp"
#include "pipelines/sort.cpp"
#include "pipelines/sum.cpp"

namespace Verifier {
static std::list<Pipeline>* pipelinesRef = NULL;

PipelineAutoReg::PipelineAutoReg(std::string name,
                                 int numArgs,
                                 bool (*cb)(AST::Query*,
                                            Value::Call*,
                                            std::vector<Value::Container>,
                                            Type::Container&)) {
  static std::list<Pipeline> pipelines;
  pipelinesRef = &pipelines;
  Pipeline pipeline;
  pipeline.cb = cb;
  pipeline.numArgs = numArgs;
  pipeline.name = name;
  pipelines.push_back(pipeline);
}

bool verifyCall(AST::Query* query,
                Value::Call* call,
                Type::Container& resultType) {
  assert(pipelinesRef != NULL);
  int argNum = -1;
  std::list<Pipeline>::iterator pipeline = pipelinesRef->begin();

  for (; pipeline != pipelinesRef->end(); ++pipeline) {
    if ((*pipeline).name == call->getCalleeName()) {
      argNum = (*pipeline).numArgs;
      if (argNum == call->numArguments()) {
        return (*pipeline).cb(query, call, call->getArguments(), resultType);
      }
    }
  }

  Diagnostics::Controller::report(
      argNum < 0 ? Diagnostics::Error::cannotResolveName(call)
                 : Diagnostics::Error::wrongNumberOfArguments(argNum, call));
  return false;
}

}  // namespace Verifier