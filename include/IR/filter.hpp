#ifndef __MARKUS_IR_FILTER__
#define __MARKUS_IR_FILTER__

namespace IR {
/**
 * For every possible filter there is a number.
 */
enum FilterKind { FILTER_KIND_IS };

/**
 * The filter representation that provides answers to queries about a filter.
 */
class Filter {
 private:
  /**
   * Kind of the query.
   */
  enum FilterKind kind;

 public:
  /**
   * Constructs a new query with the given kind.
   */
  Filter(enum FilterKind kind);

  /**
   * Returns whatever this is a `is` filter.
   */
  bool isIs();
};
}  // namespace IR

#endif