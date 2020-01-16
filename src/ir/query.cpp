#include "ir/query.hpp"

#include <iostream>

namespace IR {
Query::Query(AST::Query* query) {
  std::vector<AST::PipelineInfo> pipelines = query->getPipelines();
  std::vector<AST::PipelineInfo>::iterator pipeline;

  std::vector<Type::Uri> sortedBy;
  FilterCollection filterCollection;

  for (pipeline = pipelines.begin(); pipeline != pipelines.end(); ++pipeline) {
    Value::Call* call = pipeline->call;
    std::string name = call->getCalleeName();
    std::vector<Value::Container> arguments = call->getArguments();

    if (name == "sort") {
      sortedBy.push_back(*arguments[0].asVariable()->getMember());
      continue;
    }

    if (name == "eq" || name == "neq" || name == "lt" || name == "lte" ||
        name == "gt" || name == "gte") {
      filterCollection.add(Filter::Binary(call));
      continue;
    }

    if (name == "is") {
      filterCollection.add(Filter::Unary(call));
      continue;
    }

    std::cerr << "The " << name
              << " pipeline is not yet supported in the IR phase." << std::endl;
    abort();
  }

  if (filterCollection.isEmpty() && sortedBy.empty())
    return;

  Layer layer = Layer(new ListLayer(filterCollection));
  for (int i = 0; i < sortedBy.size(); ++i)
    layer.asListLayer()->sort(sortedBy[i]);
  layers.push_back(layer);
}

std::vector<Layer> Query::getLayers() {
  return layers;
}
}  // namespace IR