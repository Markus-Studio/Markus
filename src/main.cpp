#include <iostream>
#include <string>
#include "type/atomic.hpp"

using namespace std;

int main() {
    cout << "Hello World!" << endl;

    Type::Atomic type("test");

    type.printName();
}