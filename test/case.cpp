#include "test.hpp"

TEST("Hello") {
  UNIT("S", { CHECK(1 == 1); });
  UNIT("URP", { CHECK(1 == 1); });

  UNIT("PEEXX", {
    UNIT("D", { CHECK(1 == 1); });
    UNIT("F", { CHECK(1 == 1); });
  });
}