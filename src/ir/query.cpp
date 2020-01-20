#include "ir/query.hpp"

#include <iostream>

namespace IR {
std::pair<std::vector<Layer>, Type::Uri> compile(AST::Query* query) {
  std::vector<Layer> layers;
  std::vector<AST::PipelineInfo> pipelines = query->getPipelines();
  std::vector<AST::PipelineInfo>::iterator pipeline = pipelines.begin();

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

      if (name == "groupBy")
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

    if (pipeline == pipelines.end()) {
      if (layers.empty()) {
        ListLayer* listLayer = new ListLayer(collection);
        for (int i = 0; i < sortedBy.size(); ++i)
          listLayer->sort(sortedBy[i]);
        layers.push_back(Layer(listLayer));
      } else {
        goto error;
      }
      break;
    }

    if (name == "groupBy") {
      if (!layers.empty())
        goto error;

      GroupLayer* groupLayer = new GroupLayer(collection);

      // Parse the next thing.
      ++pipeline;
      continue;
    }
  }

  return std::pair<std::vector<Layer>, Type::Uri>(layers, selected);

error:
  std::cerr << "Failed to transform the query into a valid MarkusIR."
            << std::endl
            << "If you think your query makes sense and should be compiled "
               "with no problems please file a bug report containing the query "
               "so we can support that!"
            << std::endl;
  abort();
}

Query::Query(AST::Query* query) {
  std::pair<std::vector<Layer>, Type::Uri> compilationResult = compile(query);
  layers = compilationResult.first;
  // TODO(qti3e) What should we do with the selected :/
}

std::vector<Layer> Query::getLayers() {
  return layers;
}
}  // namespace IR