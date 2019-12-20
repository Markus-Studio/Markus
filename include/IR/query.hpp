#ifndef __MARKUS_IR_QUERY__
#define __MARKUS_IR_QUERY__

#include <list>
#include <vector>

#include "IR/filter.hpp"
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
  Program* owner;

  /**
   * The return type of this query.
   */
  Type::Container* resultType;

  /**
   * Type of parameters.
   */
  std::vector<Type::Container*> parameters;

  /**
   * List of every filter in this query.
   */
  std::list<Filter> filters;

 public:
  /**
   * Constructs a new Query IR.
   */
  Query(Program* program);

  /**
   * Constructs a new Query IR with the intialized type.
   */
  Query(Program* program, Type::Container* type);

  /**
   * Add a new parameter to this query, returns the parameter id.
   */
  int addParameter(Type::Container* type);

  /**
   * Returns type of the n-th parameter.
   */
  Type::Container* getParameterType(int n);

  /**
   * Adds a `is` filter to this query, returns false on the failure the error
   * is reported using the Diagnostics.
   */
  bool is(std::string name);
};
}  // namespace IR

#endif