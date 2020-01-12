#include "type/container.hpp"

#include <assert.h>

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

}  // namespace Type