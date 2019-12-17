#include <iostream>

#include "../test.hpp"
#include "type/atomic.hpp"
#include "type/object.hpp"
#include "type/union.hpp"

using namespace Type;

namespace {
TEST("is") {
  Atomic x("x");
  Atomic y("y");
  Atomic z("z");

  Object D("D");
  Object C("D", &D);
  Object B("D");
  Object A("A", &B, &C);
  Object E("E", &C);
  Object F("F", &E);
  Object J("J", &F);
  Object M("M");
  Object L("L");

  // ø
  Union Empty;
  // x | y
  Union XorY;
  XorY.add(&x);
  XorY.add(&y);
  // y | z
  Union YorZ;
  YorZ.add(&y);
  YorZ.add(&z);
  // x | y | A
  Union XorYorA = XorY.clone();
  XorYorA.add(&A);
  // A | L
  Union AorL;
  AorL.add(&A);
  AorL.add(&L);
  // L | M
  Union LorM;
  LorM.add(&L);
  LorM.add(&M);
  // B | C
  Union BorC;
  BorC.add(&B);
  BorC.add(&C);
  // C | D
  Union CorD;
  CorD.add(&C);
  CorD.add(&D);
  // x | A
  Union XorA;
  XorA.add(&x);
  XorA.add(&A);
  // x | B
  Union XorB;
  XorB.add(&x);
  XorB.add(&B);
  // x | A | L
  Union XorAorL = XorA.clone();
  XorAorL.add(&L);
  // A | E
  Union AorE;
  AorE.add(&A);
  AorE.add(&E);
  // A | E | B
  Union AorEorB = AorE.clone();
  AorEorB.add(&B);
  // J | F
  Union JorF;
  JorF.add(&J);
  JorF.add(&F);

  CHECK(1 == x.is(&x));
  CHECK(0 == x.is(&y));
  CHECK(1 == x.is(&XorY));
  CHECK(0 == x.is(&YorZ));
  CHECK(1 == x.is(&XorYorA));
  CHECK(0 == x.is(&Empty));

  CHECK(1 == A.is(&A));
  CHECK(1 == A.is(&B));
  CHECK(0 == B.is(&A));
  CHECK(0 == B.is(&C));
  CHECK(1 == A.is(&D));
  CHECK(0 == A.is(&L));
  CHECK(1 == A.is(&AorL));
  CHECK(1 == A.is(&XorA));
  CHECK(1 == A.is(&XorAorL));
  CHECK(0 == A.is(&LorM));
  CHECK(1 == A.is(&BorC));
  CHECK(1 == A.is(&CorD));
  CHECK(1 == A.is(&XorYorA));
  CHECK(0 == A.is(&Empty));
  CHECK(1 == J.is(&D));

  CHECK(1 == XorY.is(&XorY));
  CHECK(0 == XorY.is(&Empty));
  CHECK(1 == XorY.is(&XorYorA));
  CHECK(0 == XorY.is(&x));
  CHECK(0 == XorY.is(&z));

  CHECK(1 == XorA.is(&XorA));
  CHECK(0 == XorA.is(&x));
  CHECK(1 == XorA.is(&XorB));
  CHECK(1 == XorA.is(&XorAorL));

  CHECK(1 == AorE.is(&C));
  CHECK(1 == JorF.is(&E));
  CHECK(0 == AorL.is(&C));
  CHECK(0 == AorEorB.is(&C));
  CHECK(1 == AorEorB.is(&BorC));
  CHECK(0 == BorC.is(&A));
}
}