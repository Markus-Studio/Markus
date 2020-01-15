#include "IR/query.hpp"

#include <assert.h>

#include "IR/program.hpp"
#include "verifier/verifier.hpp"

namespace IR {
Query::Query(Program* program) {
  owner = program;
  resultType = new Type::Container(program->arrayOfTypes());
}

Query::Query(Program* program, Type::Container* type) {
  owner = program;
  resultType = type;
}

int Query::addParameter(std::string name, Type::Container* type) {
  parameters.push_back(type);
  parameterNames.push_back(name);
  return parameters.size();
}

int Query::getParameterId(std::string name) {
  for (int i = 0; i < parameterNames.size(); ++i)
    if (parameterNames[i] == name)
      return i + 1;
  return -1;
}

Type::Container* Query::getParameterType(int n) {
  assert(n >= 0);
  // The first variable is always refering to the current item.
  if (n == 0)
    return resultType;
  return parameters[n - 1];
}

Program* Query::getOwner() {
  return owner;
}

bool Query::addPipeline(Value::Call* call) {
  struct PipelineInfo info;
  info.inputType = resultType;
  info.shape = resultType->getShape();
  info.call = call;
  pipelines.push_back(info);

  return Verifier::verifyCall(this, call, resultType);
}

Query* Query::getSubQuery(Value::Call* call) {
  if (call->getCalleeName() == "groupBy" && call->numArguments() == 1) {
    Query* query = new Query(owner, resultType);
    return query;
  }

  return NULL;
}

Type::Container* Query::getResultType() {
  return resultType;
}

std::vector<PipelineInfo> Query::getPipelines() {
  std::vector<PipelineInfo> result;
  result.assign(pipelines.begin(), pipelines.end());
  return result;
}
}  // namespace IR