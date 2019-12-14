#include "type/union.hpp"
#include "type/atomic.hpp"
#include "type/object.hpp"

namespace Type
{
Union::Union() {}

Union Union::clone()
{
    Union newUnion;
    newUnion.atomicMembers.assign(atomicMembers.begin(), atomicMembers.end());
    return newUnion;
}

void Union::add(Atomic type)
{
    if (!has(type))
        atomicMembers.push_back(type);
}

bool Union::has(Atomic type)
{
    std::list<Atomic>::iterator itr;
    for (itr = atomicMembers.begin(); itr != atomicMembers.end(); ++itr)
        if (itr->is(type))
            return true;
    return false;
}

void Union::add(Union type)
{
    Atomic *atomic;
    std::list<Atomic>::iterator itr;
    for (itr = type.atomicMembers.begin(); itr != type.atomicMembers.end(); ++itr)
    {
        atomic = &*itr;
        add(*atomic);
    }
}

void Union::add(Object object)
{
    if (!has(object))
        objectMembers.push_back(object);
}

bool Union::has(Object object)
{
    std::list<Object>::iterator itr;
    for (itr = objectMembers.begin(); itr != objectMembers.end(); ++itr)
        if (itr->getId() == object.getId())
            return true;
    return false;
}

bool Union::isEmpty()
{
    return atomicMembers.empty() && objectMembers.empty();
}

} // namespace Type
