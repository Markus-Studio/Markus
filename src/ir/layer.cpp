#include "ir/layer.hpp"

#include <assert.h>

namespace IR {
Layer::Layer() {
  kind = LAYER_NO_LAYER;
  layer = NULL;
}

Layer::Layer(ListLayer* listLayer) {
  kind = LAYER_LIST;
  layer = listLayer;
}

bool Layer::isListLayer() {
  return kind == LAYER_LIST;
}

ListLayer* Layer::asListLayer() {
  assert(kind == LAYER_LIST);
  return (ListLayer*)layer;
}

enum LayerKind Layer::getKind() {
  return kind;
}
}  // namespace IR