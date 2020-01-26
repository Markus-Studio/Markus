#include "ir/query.hpp"

#include <iostream>
#include <list>

#include "ir/filterCollection.hpp"

namespace IR {
/**
 * Writing a general compiler to compile a query into a list of Markus Layers
 * is extremely difficult (at least for me) so this function does a selective
 * compiling, meaning that it complies subsets of possible queries, and hence
 * there might be a query that this function fails to compile in that case it
 * just aborts the program telling user to file a support request.
 */
std::vector<Layer> compile(AST::Query* query) {
  std::vector<Layer> layers;
  std::vector<AST::PipelineInfo> pipelines = query->getPipelines();
  std::vector<AST::PipelineInfo>::iterator pipeline = pipelines.begin();

  while (pipeline != pipelines.end()) {
    std::list<Filter> filters;
    Type::Uri selected;
    Value::Call* call;
    std::string calleeName;

    for (; pipeline != pipelines.end(); ++pipeline) {
      selected = pipeline->selected;
      call = pipeline->call;
      calleeName = call->getCalleeName();

      if (calleeName == "select")
        continue;

      if (calleeName == "is") {
        Filter filter = Filter::Unary(call);
        Filter::applySelected(filter, selected);
        filters.push_back(filter);
        continue;
      }

      if (calleeName == "eq" || calleeName == "neq" || calleeName == "lt" ||
          calleeName == "gt" || calleeName == "lte" || calleeName == "gte") {
        Filter filter = Filter::Binary(call);
        Filter::applySelected(filter, selected);
        filters.push_back(filter);
        continue;
      }

      if (calleeName == "groupBy")
        break;

      goto error;
    }

    // ========================================================================
    // GENERATION                                                             =
    // ========================================================================

    if (pipeline == pipelines.end()) {
      if (!layers.empty())
        goto error;

      Layers::List* listLayer = new Layers::List();
      listLayer->select(selected);
      std::list<Filter>::iterator it;
      for (it = filters.begin(); it != filters.end(); ++it)
        listLayer->filter(*it);
      layers.push_back(Layer(listLayer));
      continue;
    }

    if (calleeName == "groupBy") {
      if (!layers.empty())
        goto error;
      std::vector<Value::Container> args = call->getArguments();

      if (args.size() == 2)
        goto error;  // TODO(qti3e)

      Type::Uri axis = *args[0].asVariable()->getMember();

      Layers::GroupBy* groupByLayer = new Layers::GroupBy(axis);
      Layers::List* listLayer = new Layers::List();

      std::list<Filter>::iterator it;
      for (it = filters.begin(); it != filters.end(); ++it)
        if (!groupByLayer->filter(*it))
          listLayer->filter(*it);

      layers.push_back(Layer(groupByLayer));
      layers.push_back(Layer(listLayer));
      pipeline++;
      continue;
    }

    goto error;
  }

  return layers;

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
  layers = compile(query);
}

std::vector<Layer> Query::getLayers() {
  return layers;
}
}  // namespace IR