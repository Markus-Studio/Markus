#include <iostream>
#include "tests.hpp"
#include "type/atomic.hpp"
#include "type/union.hpp"
#include "type/uri.hpp"

void test_atomic()
{
    Type::Atomic atomicString("string");
    Type::Atomic atomicInt("int");
    Type::Atomic atomicFloat("float");

    assert(atomicString.is(&atomicString) == true);
    assert(atomicString.is(&atomicInt) == false);
    assert(atomicInt.getName() == "int");

    Type::Union union1;
    Type::Union union2;
    Type::Union union3;

    assert(union1.isEmpty() == true);
    assert(union2.isEmpty() == true);
    assert(union3.isEmpty() == true);

    assert(union1.has(&atomicString) == false);
    assert(atomicString.is(&union1) == false);

    union1.add(&atomicString);
    assert(union1.isEmpty() == false);

    assert(union1.has(&atomicString) == true);
    assert(atomicString.is(&union1) == true);

    union2 = union1.clone();
    assert(union2.has(&atomicString) == true);
    assert(atomicString.is(&union2) == true);
    assert(union2.isEmpty() == false);

    union2.add(&atomicFloat);
    assert(union2.has(&atomicFloat) == true);
    assert(atomicFloat.is(&union2) == true);

    assert(union1.has(&atomicFloat) == false);
    assert(atomicFloat.is(&union1) == false);

    union3.add(&union1);
    union3.add(&union2);
    assert(union3.isEmpty() == false);

    assert(union3.has(&atomicString) == true);
    assert(union3.has(&atomicFloat) == true);
    assert(union3.has(&atomicInt) == false);

    std::cout << "done: test_atomic" << std::endl;
}
