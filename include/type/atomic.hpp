#ifndef _MARKUS_TYPE_ATOMIC
#define _MARKUS_TYPE_ATOMIC

#include <string>

namespace Type {
    using namespace std;

    class Atomic
    {
    public:
        string name;
        Atomic(string _name);
        void printName();
    };
}

#endif