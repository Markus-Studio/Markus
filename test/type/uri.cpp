#include "type/uri.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "../test.hpp"

namespace {
TEST("uri") {
  Type::Uri uri, uri2;
  std::vector<std::string> units;

  CHECK(uri.isEmpty() == true);

  uri = Type::Uri("A", "B");
  CHECK(uri.isEmpty() == false);

  units = uri.getUnits();
  CHECK(units.size() == 2);
  CHECK(units[0] == "A");
  CHECK(units[1] == "B");

  uri2 = uri.popFirst();
  units = uri2.getUnits();
  CHECK(units.size() == 1);
  CHECK(units[0] == "B");

  units = uri.getUnits();
  CHECK(units.size() == 2);
  CHECK(units[0] == "A");
  CHECK(units[1] == "B");
}
}  // namespace