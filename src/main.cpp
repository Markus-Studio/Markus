#include <iostream>
#include <string>

#include "type/union.hpp"
#include "type/atomic.hpp"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    Type::Atomic atomicString("string");
    Type::Atomic atomicInt("int");
    Type::Atomic atomicFloat("float");

    Type::Union union1;

    cout << union1.has(atomicString) << endl;
    union1.add(atomicString);
    cout << union1.has(atomicString) << endl;

    Type::Union union2 = union1.clone();
    cout << union2.has(atomicString) << endl;
    cout << union2.has(atomicInt) << endl;
    union2.add(atomicInt);
    cout << union2.has(atomicInt) << endl;
    cout << union1.has(atomicInt) << endl;

    union1.add(union2);
    cout << union1.has(atomicInt) << endl;
}