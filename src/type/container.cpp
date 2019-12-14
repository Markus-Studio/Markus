#include <assert.h>
#include "type/atomic.hpp"
#include "type/union.hpp"
#include "type/object.hpp"
#include "type/container.hpp"

namespace Type
{
TypeKind Container::getKind()
{
    return kind;
}

Container::Container()
{
    kind = TYPE_KIND_NEVER;
}

bool Container::isNever()
{
    return kind == TYPE_KIND_NEVER;
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

bool Container::is(Atomic *type)
{
    switch (kind)
    {
    case TYPE_KIND_NEVER:
    case TYPE_KIND_OBJECT:
        return false;
    case TYPE_KIND_ATOMIC:
        return asAtomic()->is(type);
    case TYPE_KIND_UNION:
        return asUnion()->is(type);
    }
}

bool Container::is(Union *type)
{
    switch (kind)
    {
    case TYPE_KIND_NEVER:
        return false;
    case TYPE_KIND_ATOMIC:
        return asAtomic()->is(type);
    case TYPE_KIND_OBJECT:
        return asObject()->is(type);
    case TYPE_KIND_UNION:
        return asUnion()->is(type);
    }
}

bool Container::is(Object *type)
{
    switch (kind)
    {
    case TYPE_KIND_NEVER:
    case TYPE_KIND_ATOMIC:
        return false;
    case TYPE_KIND_OBJECT:
        return asObject()->is(type);
    case TYPE_KIND_UNION:
        return asUnion()->is(type);
    }
}

} // namespace Type