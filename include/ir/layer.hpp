#ifndef __MARKUS_IR_LAYER__
#define __MARKUS_IR_LAYER__

namespace IR {
enum LayerKind {
  /**
   * The list layer is responsible to store an ordered/unordered set of things,
   * the reader can have a dynamic filter to filter data on demand.
   */
  LAYER_LIST,
  /**
   * The index layer connects the current layer to the next layer based on some
   * parameters.
   */
  LAYER_INDEX,
  /**
   * The group layer is used for the groupBy pipeline.
   */
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

 public:
  /**
   * Returns kind of this layer.
   */
  enum LayerKind getKind();
};
}  // namespace IR

#endif