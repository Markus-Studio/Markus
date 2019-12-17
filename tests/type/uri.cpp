#include "type/uri.hpp"

#include <assert.h>

#include <iostream>
#include <string>
#include <vector>

#include "tests.hpp"

void test_uri() {
  Type::Uri uri, uri2;
  std::vector<std::string> units;

  assert(uri.isEmpty() == true);

  uri = Type::Uri("A", "B");
  assert(uri.isEmpty() == false);

  units = uri.getUnits();
  assert(units.size() == 2);
  assert(units[0] == "A");
  assert(units[1] == "B");

  uri2 = uri.popFirst();
  units = uri2.getUnits();
  assert(units.size() == 1);
  assert(units[1] == "B");

  units = uri.getUnits();
  assert(units.size() == 2);
  assert(units[0] == "A");
  assert(units[1] == "B");

  std::cout << "done: test_uri" << std::endl;
}