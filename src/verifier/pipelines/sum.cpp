#include "verifier/verifier.hpp"

MARKUS_PIPELINE(sum, 0) {
  EXPECT_TYPE_SHAPE(resultType, 1);
  EXPECT_TYPE(IS_NUMBER(resultType->asArray()->getContainedType()), "number");
  resultType = resultType->asArray()->getContainedType();
  return true;
}

MARKUS_PIPELINE(sum, 1) {
  EXPECT_ARG_FIELD(0);
  EXPECT_ARG_FIELD_EXISTS(0);
  Type::Container* type = arguments[0]->asVariable()->getType();
  EXPECT_TYPE_SHAPE(type, 1);
  type = type->asArray()->getContainedType();
  EXPECT_TYPE(IS_NUMBER(type), "number");
  resultType = type;
  return true;
}