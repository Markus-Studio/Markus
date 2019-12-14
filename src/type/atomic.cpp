#include <string>
#include "type/atomic.hpp"
#include "type/union.hpp"

using namespace std;

namespace Type
{
Atomic::Atomic(string name)
{
    this->name = name;
}

string Atomic::getName()
{
    return name;
}

bool Atomic::is(Atomic *type)
{
    return name == type->name;
}

bool Atomic::is(Union *type)
{
    return type->has(this);
}
} // namespace Type