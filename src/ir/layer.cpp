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

Layer::Layer(Layers::GroupBy* layer) {
  kind = LAYER_GROUP_BY;
  this->layer = layer;
}

bool Layer::isGroupByLayer() {
  return kind == LAYER_GROUP_BY;
}

Layers::GroupBy* Layer::asGroupByLayer() {
  assert(kind == LAYER_GROUP_BY);
  return (Layers::GroupBy*)layer;
}

Layer::Layer(Layers::Index* layer) {
  kind = LAYER_INDEX;
  this->layer = layer;
}

bool Layer::isIndexLayer() {
  return kind == LAYER_INDEX;
}

Layers::Index* Layer::asIndexLayer() {
  assert(kind == LAYER_INDEX);
  return (Layers::Index*)layer;
}
}  // namespace IR