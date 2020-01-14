#include "verifier/verifier.hpp"

MARKUS_PIPELINE(is, 1) {
  EXPECT_ARG_KIND(0, Value::VALUE_KIND_TYPE);

  Type::Container* type = arguments[0]->asType()->getType();
  resultType = resultType->extract(type);

  return true;
}