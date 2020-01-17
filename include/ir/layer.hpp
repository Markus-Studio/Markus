#ifndef __MARKUS_IR_LAYER__
#define __MARKUS_IR_LAYER__

#include "ir/layers/list.hpp"

namespace IR {
enum LayerKind {
  // Indicates that the layers is not initialized yet.
  LAYER_NO_LAYER,
  LAYER_LIST,
  LAYER_INDEX,
  LAYER_GROUP,
  /**
   * An aggregation layer deals with pipelines such as sum, avg, etc.
   */
  LAYER_AGGREGATION
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
   * Constructs a layer containing a list layer.
   */
  Layer(ListLayer* listLayer);

  /**
   * Returns true if the contained layer is a list layer.
   */
  bool isListLayer();

  /**
   * Returns the contained layer supposing it's a list layer, aborts otherwise.
   */
  ListLayer* asListLayer();

  /**
   * Returns kind of this layer.
   */
  enum LayerKind getKind();
};
}  // namespace IR

#endif