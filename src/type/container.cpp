#include "type/container.hpp"

#include <assert.h>

#include <iostream>

#include "type/array.hpp"
#include "type/atomic.hpp"
#include "type/object.hpp"
#include "type/union.hpp"

namespace Type {
TypeKind Container::getKind() {
  return kind;
}

Container::Container() {
  kind = TYPE_KIND_NEVER;
}

bool Container::isNever() {
  return kind == TYPE_KIND_NEVER;
}

Container::Container(Atomic* a) {
  kind = TYPE_KIND_ATOMIC;
  type = a;
}

Atomic* Container::asAtomic() {
  assert(kind == TYPE_KIND_ATOMIC);
  return (Atomic*)type;
}

bool Container::isAtomic() {
  return kind == TYPE_KIND_ATOMIC;
}

Container::Container(Union* u) {
  kind = TYPE_KIND_UNION;
  type = u;
}

Union* Container::asUnion() {
  assert(kind == TYPE_KIND_UNION);
  return (Union*)type;
}

bool Container::isUnion() {
  return kind == TYPE_KIND_UNION;
}

Container::Container(Object* o) {
  kind = TYPE_KIND_OBJECT;
  type = o;
}

Object* Container::asObject() {
  assert(kind == TYPE_KIND_OBJECT);
  return (Object*)type;
}

bool Container::isObject() {
  return kind == TYPE_KIND_OBJECT;
}

Container::Container(Array* a) {
  kind = TYPE_KIND_ARRAY;
  type = a;
}

Array* Container::asArray() {
  assert(kind == TYPE_KIND_ARRAY);
  return (Array*)type;
}

bool Container::isArray() {
  return kind == TYPE_KIND_ARRAY;
}

bool Container::is(Container* type) {
  switch (type->kind) {
    case TYPE_KIND_NEVER:
      return false;
    case TYPE_KIND_ATOMIC:
      return is(type->asAtomic());
    case TYPE_KIND_UNION:
      return is(type->asUnion());
    case TYPE_KIND_OBJECT:
      return is(type->asObject());
    case TYPE_KIND_ARRAY:
      return is(type->asArray());
  }
}

bool Container::is(Atomic* type) {
  switch (kind) {
    case TYPE_KIND_NEVER:
    case TYPE_KIND_OBJECT:
    case TYPE_KIND_ARRAY:
      return false;
    case TYPE_KIND_ATOMIC:
      return asAtomic()->is(type);
    case TYPE_KIND_UNION:
      return asUnion()->is(type);
  }
}

bool Container::is(Union* type) {
  switch (kind) {
    case TYPE_KIND_NEVER:
    case TYPE_KIND_ARRAY:
      return false;
    case TYPE_KIND_ATOMIC:
      return asAtomic()->is(type);
    case TYPE_KIND_OBJECT:
      return asObject()->is(type);
    case TYPE_KIND_UNION:
      return asUnion()->is(type);
  }
}

bool Container::is(Object* type) {
  switch (kind) {
    case TYPE_KIND_NEVER:
    case TYPE_KIND_ATOMIC:
    case TYPE_KIND_ARRAY:
      return false;
    case TYPE_KIND_OBJECT:
      return asObject()->is(type);
    case TYPE_KIND_UNION:
      return asUnion()->is(type);
  }
}

bool Container::is(Array* type) {
  if (kind == TYPE_KIND_ARRAY)
    return asArray()->is(type);
  return false;
}

int Container::getShape() {
  if (!isArray())
    return 0;

  return 1 + asArray()->getContainedType()->getShape();
}

Container* Container::query(Uri uri) {
  if (uri.isEmpty())
    return this;

  switch (kind) {
    case TYPE_KIND_NEVER:
    case TYPE_KIND_ATOMIC:
      return new Container();

    case TYPE_KIND_ARRAY:
      return new Container(asArray()->query(uri));

    case TYPE_KIND_OBJECT:
      return asObject()->query(uri);

    case TYPE_KIND_UNION:
      return asUnion()->query(uri);
  }

  assert(0);
}

Container* Container::extract(Container* baseType) {
  switch (kind) {
    case TYPE_KIND_NEVER:
      return this;

    case TYPE_KIND_ATOMIC:
    case TYPE_KIND_OBJECT:
      if (this->is(baseType))
        return this;
      return new Container();

    case TYPE_KIND_ARRAY:
      return new Container(
          new Array(asArray()->getContainedType()->extract(baseType)));

    case TYPE_KIND_UNION:
      Union* result = new Union();
      Union* u = asUnion();
      Container c = Container();
      std::list<Atomic*>::iterator aIt = u->atomicMembers.begin();
      c.kind = TYPE_KIND_ATOMIC;
      for (c.type = *aIt; aIt != u->atomicMembers.end(); ++aIt, c.type = *aIt)
        if (c.is(baseType))
          result->add(*aIt);
      std::list<Object*>::iterator oIt = u->objectMembers.begin();
      c.kind = TYPE_KIND_OBJECT;
      for (c.type = *oIt; oIt != u->objectMembers.end(); ++oIt, c.type = *oIt)
        if (c.is(baseType))
          result->add(*oIt);
      return new Container(result);
  }
}

bool Container::isNil() {
  switch (kind) {
    case TYPE_KIND_NEVER:
      return true;

    case TYPE_KIND_ATOMIC:
    case TYPE_KIND_OBJECT:
      return false;

    case TYPE_KIND_ARRAY:
      return asArray()->getContainedType()->isNil();

    case TYPE_KIND_UNION:
      return asUnion()->isEmpty();
  }

  assert(0);
}

void Container::dump() {
  if (isNil()) {
    std::cout << "NIL" << std::endl;
    return;
  }

  switch (kind) {
    case TYPE_KIND_NEVER:
      std::cout << "NEVER" << std::endl;
      return;

    case TYPE_KIND_ATOMIC:
      std::cout << asAtomic()->getName() << std::endl;
      return;

    case TYPE_KIND_OBJECT:
      std::cout << asObject()->getName() << std::endl;
      return;

    case TYPE_KIND_ARRAY:
      std::cout << "Array<" << std::endl;
      asArray()->getContainedType()->dump();
      std::cout << ">" << std::endl;
      return;

    case TYPE_KIND_UNION: {
      std::cout << "Union<" << std::endl;
      Union* u = asUnion();
      Container c = Container();
      std::list<Atomic*>::iterator aIt = u->atomicMembers.begin();
      std::list<Object*>::iterator oIt = u->objectMembers.begin();
      for (; aIt != u->atomicMembers.end(); ++aIt) {
        c.kind = TYPE_KIND_ATOMIC;
        c.type = *aIt;
        c.dump();
      }

      for (; oIt != u->objectMembers.end(); ++oIt) {
        c.kind = TYPE_KIND_OBJECT;
        c.type = *oIt;
        c.dump();
      }
      std::cout << ">" << std::endl;
    }
  }
}

}  // namespace Type