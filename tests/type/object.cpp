#include "type/object.hpp"

#include <assert.h>

#include <iostream>

#include "tests.hpp"
#include "type/atomic.hpp"
#include "type/container.hpp"
#include "type/uri.hpp"

using namespace Type;

void test_object() {
  Atomic x("x");
  Atomic y("y");
  Object o1("test");
  Object o2("object", &o1);
  Object o3("obj", &o2);
  Object o4("foo");
  Uri u1("o", "a");
  Uri u2("o", "b");
  Uri u3("o", "c");
  Container c;

  assert(o1.getName() == "test");
  assert(o2.getName() == "object");
  assert(o3.getName() == "obj");
  assert(o4.getName() == "foo");
  assert(o2.getId() > o1.getId());
  assert(o3.getId() > o2.getId());
  assert(o4.getId() > o3.getId());

  o1.set("a", &x, false);
  o3.set("b", &y, false);
  o4.set("o", &o3, false);

  assert(o1.owns("b") == false);
  assert(o1.owns("a") == true);
  assert(o1.has("b") == false);
  assert(o1.has("a") == true);

  assert(o2.owns("b") == false);
  assert(o2.owns("a") == false);
  assert(o2.has("b") == false);
  assert(o2.has("a") == true);

  assert(o3.owns("b") == true);
  assert(o3.owns("a") == false);
  assert(o3.has("b") == true);
  assert(o3.has("a") == true);

  assert(o4.owns("o") == true);
  assert(o4.has("o") == true);

  assert(o4.has(u1) == true);
  assert(o4.has(u2) == true);
  assert(o4.has(u3) == false);

  c = o1.query("a");
  assert(c.isAtomic());
  assert(c.asAtomic()->getName() == "x");

  c = o3.query("b");
  assert(c.isAtomic());
  assert(c.asAtomic()->getName() == "y");

  c = o3.query("xxx");
  assert(c.isNever());

  c = o4.query(u1);
  assert(c.isAtomic());
  assert(c.asAtomic()->getName() == "x");

  c = o4.query(u2);
  assert(c.isAtomic());
  assert(c.asAtomic()->getName() == "y");

  c = o4.query(u3);
  assert(c.isNever());

  c = o3.query(u3);
  assert(c.isNever());

  std::cout << "done: test_object" << std::endl;
}