#include "ir/query.hpp"

#include <iostream>

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

  // TODO(qti3e)

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