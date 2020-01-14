#include "verifier/verifier.hpp"

MARKUS_PIPELINE(select, 1) {
  EXPECT_ARG_FIELD(0);
  EXPECT_ARG_FIELD_EXISTS(0);

  resultType = arguments[0]->asVariable()->getType();
  return true;
}