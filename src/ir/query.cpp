#include "ir/query.hpp"

#include <iostream>

namespace IR {

Query::Query(AST::Query* query) {
  std::vector<AST::PipelineInfo> pipelines = query->getPipelines();
  std::vector<AST::PipelineInfo>::iterator pipeline;

  Type::Uri selected;
  std::vector<Type::Uri> sortedBy;

  while (pipeline != pipelines.end()) {
    Value::Call* call;
    std::string name;
    std::vector<Value::Container> arguments;

    FilterCollection collection;
    bool groupBy = false;
    bool aggregation = false;

    for (; pipeline != pipelines.end(); ++pipeline) {
      call = pipeline->call;
      name = call->getCalleeName();
      arguments = call->getArguments();

      if (name == "groupBy" || name == "sum")
        break;

      if (name == "sort") {
        Type::Uri uri = *arguments[0].asVariable()->getMember();
        uri.prepend(selected);
        sortedBy.push_back(uri);
        continue;
      }

      if (name == "eq" || name == "neq" || name == "lt" || name == "lte" ||
          name == "gt" || name == "gte") {
        Filter filter = Filter::Binary(call);
        Filter::applySelected(filter, selected);
        collection.add(filter);
        continue;
      }

      if (name == "is") {
        Filter filter = Filter::Unary(call);
        Filter::applySelected(filter, selected);
        collection.add(filter);
        continue;
      }

      std::cerr << "The " << name
                << " pipeline is not yet supported in the IR phase."
                << std::endl;
      abort();
    }

    if (!collection.isEmpty()) {
    }

    if (pipeline == pipelines.end())
      break;

    if (name == "groupBy") {
      continue;
    }
  }
}

std::vector<Layer> Query::getLayers() {
  return layers;
}
}  // namespace IR