#ifndef __MARKUS_INDEXER_META__
#define __MARKUS_INDEXER_META__

#include "value/variable.hpp"

namespace Indexing {
enum MetaKind {
  META_KIND_SORT,
  META_KIND_INDEX_CMP,
  META_KIND_INDEX_EXACT,
};

class Meta {
 private:
  enum MetaKind kind;

  Value::Variable* field;

  Value::Variable* value;

 public:
  static Meta* EQ(Value::Variable* lhs, Value::Variable* rhs);
  static Meta* NEQ(Value::Variable* lhs, Value::Variable* rhs);
  static Meta* LT(Value::Variable* lhs, Value::Variable* rhs);
  static Meta* GT(Value::Variable* lhs, Value::Variable* rhs);
  static Meta* LTE(Value::Variable* lhs, Value::Variable* rhs);
  static Meta* GTE(Value::Variable* lhs, Value::Variable* rhs);
  static Meta* Sort(Value::Variable* field);
};
}  // namespace Indexing

#endif