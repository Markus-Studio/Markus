#pragma once

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
};
}  // namespace IR