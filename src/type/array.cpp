#include "type/array.hpp"

namespace Type {
Array::Array(Container* type) {
  contained = type;
}

Container* Array::getContainedType() {
  return contained;
}

bool Array::is(Array* array) {
  return contained->is(array->contained);
}

bool Array::isDeep(Array* type) {
  return contained->is(type);
}

bool Array::isDeep(Atomic* type) {
  return contained->is(type);
}

bool Array::isDeep(Object* type) {
  return contained->is(type);
}

bool Array::isDeep(Union* type) {
  return contained->is(type);
}

bool Array::isDeep(Container* type) {
  return contained->is(type);
}

Array* Array::query(Uri uri) {
  if (uri.isEmpty())
    return this;
  return new Array(contained->query(uri));
}

}  // namespace Type