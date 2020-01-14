#ifndef __MARKUS_INDEXER_ENGINE__
#define __MARKUS_INDEXER_ENGINE__

#include <map>

#include "IR/query.hpp"
#include "indexer/meta.hpp"

namespace Indexer {
/**
 * The indexer engine is responsible for keeping track of indexes that are
 * useful to fetch the data in queries, the engine generates what we call
 * the Index Graph.
 */
class Engine {
 private:
  std::multimap<IR::Query*, Meta*> queryMetaData;

 public:
  void addQueryMeta(IR::Query* query, Meta* meta);
};
}  // namespace Indexer

#endif