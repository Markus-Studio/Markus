#pragma once
#include "ir/layers/groupBy.hpp"
#include "ir/layers/index.hpp"
#include "ir/layers/list.hpp"

namespace IR {
enum LayerKind {
  // Indicates that the layers is not initialized yet.
  LAYER_NO_LAYER,
  LAYER_LIST,
  LAYER_INDEX,
  LAYER_GROUP_BY,
  LAYER_AGGREGATION,
  LAYER_MAP
};

/**
 * A layer is simply a Data Proccessing Unit, each layer has it's own working
 * mechanism and we can represent Markus queries by combining multiple layers.
 *
 * It's basically a high-level representation for a particular task.
 */
class Layer {
 private:
  /**
   * The layer kind.
   */
  enum LayerKind kind;

  /**
   * Link to the layer.
   */
  void* layer;

 public:
  /**
   * Default constructor.
   */
  Layer();

  /**
   * Returns kind of this layer.
   */
  enum LayerKind getKind();

  /**
   * Returns a string representing this layer.
   */
  std::string toString();

  /**
   * Constructs a new layer containing a list layer.
   */
  Layer(Layers::List* layer);

  /**
   * Returns true if the contained list is a layer.
   */
  bool isListLayer();

  /**
   * Returns the contained layers as a list layer.
   */
  Layers::List* asListLayer();

  /**
   * Constructs a new groupBy layer.
   */
  Layer(Layers::GroupBy* layer);

  /**
   * Returns true if the contained layer is a groupBy layer.
   */
  bool isGroupByLayer();

  /**
   * Returns the contained layer as a groupBy layer.
   */
  Layers::GroupBy* asGroupByLayer();

  /**
   * Constructs a new index layer.
   */
  Layer(Layers::Index* layer);

  /**
   * Returns true if the contained layer is a index layer.
   */
  bool isIndexLayer();

  /**
   * Returns the contained layer as a index layer.
   */
  Layers::Index* asIndexLayer();
};
}  // namespace IR