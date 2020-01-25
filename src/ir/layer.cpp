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

Layer::Layer(Layers::List* layer) {
  kind = LAYER_LIST;
  this->layer = layer;
}

bool Layer::isListLayer() {
  return kind == LAYER_LIST;
}

Layers::List* Layer::asListLayer() {
  assert(kind == LAYER_LIST);
  return (Layers::List*)layer;
}
}  // namespace IR