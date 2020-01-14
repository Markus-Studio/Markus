#include "verifier/verifier.hpp"

#include <iostream>
#include <list>

namespace Verifier {
static std::list<Pipeline>* pipelinesRef;

PipelineAutoReg::PipelineAutoReg(std::string name,
                                 int numArgs,
                                 bool (*cb)(IR::Query*,
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
  std::list<Pipeline>::iterator pipeline = pipelinesRef->begin();
  for (; pipeline != pipelinesRef->end(); ++pipeline) {
    std::cout << (*pipeline).name << (*pipeline).numArgs << std::endl;
  }

  Diagnostics::Controller::report(Diagnostics::Error::cannotResolveName(call));
  return false;
}

}  // namespace Verifier