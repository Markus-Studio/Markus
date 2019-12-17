#include "type/uri.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "../test.hpp"

namespace {
TEST("uri") {
  Type::Uri uri, uri2;
  std::vector<std::string> units;

  std::cout << "AAA" << std::endl;

  CHECK(uri.isEmpty() == true);

  std::cout << "BBB" << std::endl;

  uri = Type::Uri("A", "B");
  CHECK(uri.isEmpty() == false);

  std::cout << "CCCC" << std::endl;

  units = uri.getUnits();
  CHECK(units.size() == 2);
  CHECK(units[0] == "A");
  CHECK(units[1] == "B");

  std::cout << "DDDD" << std::endl;

  uri2 = uri.popFirst();
  units = uri2.getUnits();
  CHECK(units.size() == 1);
  CHECK(units[1] == "B");

  std::cout << "EEEEE" << std::endl;

  units = uri.getUnits();
  CHECK(units.size() == 2);
  CHECK(units[0] == "A");
  CHECK(units[1] == "B");
}
}  // namespace