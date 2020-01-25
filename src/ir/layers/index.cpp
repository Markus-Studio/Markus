#include "ir/layers/index.hpp"

namespace IR {
namespace Layers {
bool Index::addFilter(Filter filter) {
  // TODO(qti3e)
  return false;
}

FilterCollection Index::getFunction() {
  return function;
}

bool Index::isFunctionEmpty() {
  return function.isEmpty();
}
}  // namespace Layers
}  // namespace IR