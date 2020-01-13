#include "indexer/engine.hpp"

namespace Indexer {
void Engine::addQueryMeta(IR::Query* query, Meta* meta) {
  if (meta != NULL)
    queryMetaData.insert(std::pair<IR::Query*, Meta*>(query, meta));
}
}  // namespace Indexer