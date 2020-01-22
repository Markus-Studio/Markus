#pragma once
#include <map>

#include "ast/query.hpp"
#include "indexer/meta.hpp"

namespace Indexer {
/**
 * The indexer engine is responsible for keeping track of indexes that are
 * useful to fetch the data in queries, the engine generates what we call
 * the Index Graph.
 */
class Engine {
 private:
  std::multimap<AST::Query*, Meta*> queryMetaData;

 public:
  void addQueryMeta(AST::Query* query, Meta* meta);
};
}  // namespace Indexer