#include "ir/layer.hpp"

#include <assert.h>

namespace IR {
Layer::Layer() {
  kind = LAYER_NO_LAYER;
  layer = nullptr;
}

enum LayerKind Layer::getKind() {
  return kind;
}
}  // namespace IR