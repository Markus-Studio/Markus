#ifndef __MARKUS_IR_QUERY__
#define __MARKUS_IR_QUERY__

#include "IR/program.hpp"
#include "type/container.hpp"

namespace IR {
/**
 * The intermediate representation for any query in the system.
 */
class Query {
  /**
   * Every query belongs to a program.
   */
  Program& owner;

  /**
   * The return type of this query.
   */
  Type::Container* type;

 public:
  /**
   * Constructs a new Query IR.
   */
  Query(Program& program);

  /**
   * Add a new parameter to this query, returns the parameter id.
   */
  int addParameter(Type::Container& type);

  /**
   * Adds a `is` filter to this query, returns false on the failure the error
   * is reported using the Diagnostics.
   */
  bool is(std::string name);
};
}  // namespace IR

#endif