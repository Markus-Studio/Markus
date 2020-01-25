#include "indexer/meta.hpp"

#include <assert.h>

namespace Indexer {
Meta* Meta::Index(enum MetaOperator op,
                  Value::Variable* lhs,
                  Value::Variable* rhs) {
  if (lhs->getId() == 0) {
    if (rhs->getId() == 0)
      return nullptr;

    Meta* result = new Meta();
    result->kind = META_KIND_INDEX;
    result->op = op;
    result->field = lhs;
    result->value = rhs;
    return result;
  }

  if (rhs->getId() == 0)
    return Meta::Index(
        op == OP_LT
            ? OP_GT
            : (op == OP_GT
                   ? OP_LT
                   : (op == OP_LTE ? OP_GTE : (op == OP_GTE ? OP_LTE : op))),
        rhs, lhs);

  return nullptr;
}

Meta* Meta::EQ(Value::Variable* lhs, Value::Variable* rhs) {
  return Index(OP_EQ, lhs, rhs);
}

Meta* Meta::NEQ(Value::Variable* lhs, Value::Variable* rhs) {
  return Index(OP_NEQ, lhs, rhs);
}

Meta* Meta::LT(Value::Variable* lhs, Value::Variable* rhs) {
  return Index(OP_LT, lhs, rhs);
}

Meta* Meta::GT(Value::Variable* lhs, Value::Variable* rhs) {
  return Index(OP_GT, lhs, rhs);
}

Meta* Meta::LTE(Value::Variable* lhs, Value::Variable* rhs) {
  return Index(OP_LTE, lhs, rhs);
}

Meta* Meta::GTE(Value::Variable* lhs, Value::Variable* rhs) {
  return Index(OP_GTE, lhs, rhs);
}

Meta* Meta::Sort(Value::Variable* field) {
  if (field->getId() != 0)
    return nullptr;
  Meta* result = new Meta();
  result->kind = META_KIND_SORT;
  result->field = field;
  result->value = nullptr;
  return result;
}

}  // namespace Indexer