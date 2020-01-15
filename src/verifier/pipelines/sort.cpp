#include "verifier/verifier.hpp"

MARKUS_PIPELINE(sort, 1) {
  EXPECT_ARG_FIELD(0);
  EXPECT_ARG_FIELD_EXISTS(0);
  Type::Container* type = arguments[0]->asVariable()->getType();
  EXPECT_TYPE(IS_NUMBER(type) || IS_BUILTIN(type, "string"),
              "number or string");
  // Index it.
  query->getOwner()->getIndexer()->addQueryMeta(
      query, Indexer::Meta::Sort(arguments[0]->asVariable()));
  return true;
}