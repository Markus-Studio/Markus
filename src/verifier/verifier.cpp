#include "verifier/verifier.hpp"

#include <iostream>
#include <list>

namespace Verifier {
static std::list<Pipeline>* pipelinesRef;

PipelineAutoReg::PipelineAutoReg(std::string name,
                                 int numArgs,
                                 bool (*cb)(IR::Query*,
                                            Value::Call*,
                                            std::vector<Value::Container*>,
                                            Type::Container*&)) {
  static std::list<Pipeline> pipelines;
  pipelinesRef = &pipelines;
  Pipeline pipeline;
  pipeline.cb = cb;
  pipeline.numArgs = numArgs;
  pipeline.name = name;
  pipelines.push_back(pipeline);
}

bool verifyCall(IR::Query* query,
                Value::Call* call,
                Type::Container*& resultType) {
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