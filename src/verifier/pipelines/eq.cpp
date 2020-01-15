#include "verifier/verifier.hpp"

MARKUS_PIPELINE(eq, 2) {
  // At least one of the arguments must be a field.
  if (!(IS_FIELD(0) || IS_FIELD(1)))
    EXPECT_ARG_FIELD(0);

  // We don't accept type reference as an argument.
  EXPECT_TYPE(!IS_TYPE_REF(0), "field");
  EXPECT_TYPE(!IS_TYPE_REF(1), "field");

  if (IS_VAR_OR_FIELD(0))
    EXPECT_ARG_FIELD_EXISTS(0);

  if (IS_VAR_OR_FIELD(1))
    EXPECT_ARG_FIELD_EXISTS(1);

  int field = IS_FIELD(0) ? 0 : 1;
  int value = field == 0 ? 1 : 0;
  Type::Container* fieldType = arguments[field]->getType(query);
  Type::Container* valueType = arguments[value]->getType(query);
  if (fieldType->isArray())
    fieldType = fieldType->asArray()->getContainedType();

  if (!valueType->is(fieldType)) {
    Diagnostics::Controller::report(Diagnostics::Error::typesNotUseableTogether(
        arguments[0], arguments[1]));
    return false;
  }

  // Index the field.
  if (IS_VAR(value))
    query->getOwner()->getIndexer()->addQueryMeta(
        query, Indexer::Meta::EQ(arguments[0]->asVariable(),
                                 arguments[1]->asVariable()));

  return true;
}