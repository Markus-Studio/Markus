#include <iostream>
#include <string>
#include "type/atomic.hpp"

using namespace std;

namespace Type {
    Atomic::Atomic(string _name) {
        name = _name;
    };

    void Atomic::printName() {
        cout << name;
    };
}