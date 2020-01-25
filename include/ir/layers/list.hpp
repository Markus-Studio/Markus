#pragma once

#include <vector>

#include "ir/aggregation.hpp"
#include "ir/filterCollection.hpp"

namespace IR {
namespace Layers {
/**
 * Declration of the list layer.
 */
class List {
 private:
  /**
   * The list layer can have a streaming aggregation.
   */
  Aggregation* aggregation;

  /**
   * All of the dynamic filters that are applied on members of this list.
   */
  FilterCollection dynamicFilter;

  /**
   * All of the static filters that are applied on members of this list.
   */
  FilterCollection staticFilter;

  /**
   * The selected field of members.
   */
  Type::Uri selected;

  /**
   * Stores all of the axises that members of this list are sorted based on.
   */
  std::vector<Type::Uri> sortedAxises;

 public:
  /**
   * Constructs a new list with no filter or anything.
   */
  List();

  /**
   * Default destructor.
   */
  ~List();

  /**
   * Returns true if the list has an aggregation function.
   */
  bool hasAggregation();

  /**
   * Returns true if the list is filtered staticly.
   */
  bool isStaticlyFiltered();

  /**
   * Returns true if the list is filtered dynamicly.
   */
  bool isDynamicallyFiltered();

  /**
   * Returns true if an specific field of the members is selected.
   */
  bool hasSelection();

  /**
   * Returns true if members of this list should be stored in a specific order.
   */
  bool isSorted();

  /**
   * Returns the aggregation aborts if there is no aggregation applied to
   * this list.
   */
  Aggregation getAggregation();

  /**
   * Sets the aggregation of this list.
   */
  void setAggregation(Aggregation aggregation);

  /**
   * Add a filter to this list.
   */
  void filter(Filter filter);

  /**
   * Returns a filterCollection containing all of the dynamic filters applied
   * on this list.
   */
  FilterCollection getDynamicFilter();

  /**
   * Returns a filterCollection containing all of the static filters applied
   * on this list.
   */
  FilterCollection getStaticFilter();

  /**
   * Returns the selected field.
   */
  Type::Uri getSelected();

  /**
   * Select a field on member of this list.
   */
  void select(Type::Uri field);

  /**
   * Returns a vector containing all of the sorting axises.
   */
  std::vector<Type::Uri> getSortAxises();

  /**
   * Sort this list using the given axis.
   */
  void sort(Type::Uri axis);
};
}  // namespace Layers
}  // namespace IR
