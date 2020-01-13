#ifndef __MARKUS_INDEXER_META__
#define __MARKUS_INDEXER_META__

#include "value/variable.hpp"

namespace Indexer {
enum MetaKind { META_KIND_SORT, META_KIND_INDEX };

enum MetaOperator { OP_LT, OP_GT, OP_LTE, OP_GTE, OP_EQ, OP_NEQ };

class Meta {
 private:
  enum MetaKind kind;

  enum MetaOperator op;
  Value::Variable* field;
  Value::Variable* value;

  static Meta* Index(enum MetaOperator op,
                     Value::Variable* lhs,
                     Value::Variable* rhs);

 public:
  static Meta* EQ(Value::Variable* lhs, Value::Variable* rhs);
  static Meta* NEQ(Value::Variable* lhs, Value::Variable* rhs);
  static Meta* LT(Value::Variable* lhs, Value::Variable* rhs);
  static Meta* GT(Value::Variable* lhs, Value::Variable* rhs);
  static Meta* LTE(Value::Variable* lhs, Value::Variable* rhs);
  static Meta* GTE(Value::Variable* lhs, Value::Variable* rhs);
  static Meta* Sort(Value::Variable* field);
};
}  // namespace Indexer

#endif