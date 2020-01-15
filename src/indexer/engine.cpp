#include "indexer/engine.hpp"

namespace Indexer {
void Engine::addQueryMeta(AST::Query* query, Meta* meta) {
  if (meta != NULL)
    queryMetaData.insert(std::pair<AST::Query*, Meta*>(query, meta));
}
}  // namespace Indexer