#include "type/object.hpp"

#include "../test.hpp"
#include "type/atomic.hpp"
#include "type/container.hpp"
#include "type/uri.hpp"

using namespace Type;

namespace {
TEST("Object") {
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

  CHECK(o1.getName() == "test");
  CHECK(o2.getName() == "object");
  CHECK(o3.getName() == "obj");
  CHECK(o4.getName() == "foo");
  CHECK(o2.getId() > o1.getId());
  CHECK(o3.getId() > o2.getId());
  CHECK(o4.getId() > o3.getId());

  o1.set("a", &x, false);
  o3.set("b", &y, false);
  o4.set("o", &o3, false);

  CHECK(o1.owns("b") == false);
  CHECK(o1.owns("a") == true);
  CHECK(o1.has("b") == false);
  CHECK(o1.has("a") == true);

  CHECK(o2.owns("b") == false);
  CHECK(o2.owns("a") == false);
  CHECK(o2.has("b") == false);
  CHECK(o2.has("a") == true);

  CHECK(o3.owns("b") == true);
  CHECK(o3.owns("a") == false);
  CHECK(o3.has("b") == true);
  CHECK(o3.has("a") == true);

  CHECK(o4.owns("o") == true);
  CHECK(o4.has("o") == true);

  CHECK(o4.has(u1) == true);
  CHECK(o4.has(u2) == true);
  CHECK(o4.has(u3) == false);

  c = o1.query("a");
  CHECK(c.isAtomic());
  CHECK(c.asAtomic()->getName() == "x");

  c = o3.query("b");
  CHECK(c.isAtomic());
  CHECK(c.asAtomic()->getName() == "y");

  c = o3.query("xxx");
  CHECK(c.isNever());

  c = o4.query(u1);
  CHECK(c.isAtomic());
  CHECK(c.asAtomic()->getName() == "x");

  c = o4.query(u2);
  CHECK(c.isAtomic());
  CHECK(c.asAtomic()->getName() == "y");

  c = o4.query(u3);
  CHECK(c.isNever());

  c = o3.query(u3);
  CHECK(c.isNever());
}
}