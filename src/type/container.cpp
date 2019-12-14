#include <assert.h>
#include "type/atomic.hpp"
#include "type/union.hpp"
#include "type/container.hpp"
#include "type/object.hpp"

namespace Type
{
TypeKind Container::getKind()
{
    return kind;
}

Container::Container(Atomic *a)
{
    kind = TYPE_KIND_ATOMIC;
    type = a;
}

Atomic *Container::asAtomic()
{
    assert(kind == TYPE_KIND_ATOMIC);
    return (Atomic *)type;
}

bool Container::isAtomic()
{
    return kind == TYPE_KIND_ATOMIC;
}

Container::Container(Union *u)
{
    kind = TYPE_KIND_UNION;
    type = u;
}

Union *Container::asUnion()
{
    assert(kind == TYPE_KIND_UNION);
    return (Union *)type;
}

bool Container::isUnion()
{
    return kind == TYPE_KIND_UNION;
}

Container::Container(Object *o)
{
    kind = TYPE_KIND_OBJECT;
    type = o;
}

Object *Container::asObject()
{
    assert(kind == TYPE_KIND_OBJECT);
    return (Object *)type;
}

bool Container::isObject()
{
    return kind == TYPE_KIND_OBJECT;
}

}