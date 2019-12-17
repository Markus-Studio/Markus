#include "type/atomic.hpp"

#include "../test.hpp"
#include "type/union.hpp"
#include "type/uri.hpp"

using namespace Type;

namespace {
TEST("Atomic") {
  Atomic atomicString("string");
  Atomic atomicInt("int");
  Atomic atomicFloat("float");

  CHECK(atomicString.is(&atomicString) == true);
  CHECK(atomicString.is(&atomicInt) == false);
  CHECK(atomicInt.getName() == "int");

  Union union1;
  Union union2;
  Union union3;

  CHECK(union1.isEmpty() == true);
  CHECK(union2.isEmpty() == true);
  CHECK(union3.isEmpty() == true);

  CHECK(union1.has(&atomicString) == false);
  CHECK(atomicString.is(&union1) == false);

  union1.add(&atomicString);
  CHECK(union1.isEmpty() == false);

  CHECK(union1.has(&atomicString) == true);
  CHECK(atomicString.is(&union1) == true);

  union2 = union1.clone();
  CHECK(union2.has(&atomicString) == true);
  CHECK(atomicString.is(&union2) == true);
  CHECK(union2.isEmpty() == false);

  union2.add(&atomicFloat);
  CHECK(union2.has(&atomicFloat) == true);
  CHECK(atomicFloat.is(&union2) == true);

  CHECK(union1.has(&atomicFloat) == false);
  CHECK(atomicFloat.is(&union1) == false);

  union3.add(&union1);
  union3.add(&union2);
  CHECK(union3.isEmpty() == false);

  CHECK(union3.has(&atomicString) == true);
  CHECK(union3.has(&atomicFloat) == true);
  CHECK(union3.has(&atomicInt) == false);
}
}  // namespace