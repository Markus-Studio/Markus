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

Layer::Layer(GroupLayer* groupLayer) {
  kind = LAYER_GROUP;
  layer = groupLayer;
}

bool Layer::isGroupLayer() {
  return kind == LAYER_GROUP;
}

GroupLayer* Layer::asGroupLayer() {
  assert(kind == LAYER_GROUP);
  return (GroupLayer*)layer;
}

enum LayerKind Layer::getKind() {
  return kind;
}
}  // namespace IR