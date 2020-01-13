#ifndef __MARKUS_INDEXER_ENGINE__
#define __MARKUS_INDEXER_ENGINE__

#include <map>

#include "IR/query.hpp"
#include "indexer/meta.hpp"

namespace Indexing {
class Engine {
 private:
  std::multimap<IR::Query*, Meta*> queryMetaData;

 public:
  void addQueryMeta(IR::Query* query, Meta* meta);
};
}  // namespace Indexing

#endif