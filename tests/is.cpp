#include <assert.h>
#include <iostream>
#include "type/atomic.hpp"
#include "type/object.hpp"
#include "type/union.hpp"

using namespace Type;

void test_is()
{
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

    assert(1 == x.is(&x));
    assert(0 == x.is(&y));
    assert(1 == x.is(&XorY));
    assert(0 == x.is(&YorZ));
    assert(1 == x.is(&XorYorA));
    assert(0 == x.is(&Empty));

    assert(1 == A.is(&A));
    assert(1 == A.is(&B));
    assert(0 == B.is(&A));
    assert(0 == B.is(&C));
    assert(1 == A.is(&D));
    assert(0 == A.is(&L));
    assert(1 == A.is(&AorL));
    assert(1 == A.is(&XorA));
    assert(1 == A.is(&XorAorL));
    assert(0 == A.is(&LorM));
    assert(1 == A.is(&BorC));
    assert(1 == A.is(&CorD));
    assert(1 == A.is(&XorYorA));
    assert(0 == A.is(&Empty));
    assert(1 == J.is(&D));

    assert(1 == XorY.is(&XorY));
    assert(0 == XorY.is(&Empty));
    assert(1 == XorY.is(&XorYorA));
    assert(0 == XorY.is(&x));
    assert(0 == XorY.is(&z));

    assert(1 == XorA.is(&XorA));
    assert(0 == XorA.is(&x));
    assert(1 == XorA.is(&XorB));
    assert(1 == XorA.is(&XorAorL));

    assert(1 == AorE.is(&C));
    assert(1 == JorF.is(&E));
    assert(0 == AorL.is(&C));
    assert(0 == AorEorB.is(&C));
    assert(1 == AorEorB.is(&BorC));
    assert(0 == BorC.is(&A));

    std::cout << "done: test_is" << std::endl;
}