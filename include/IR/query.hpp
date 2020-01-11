#ifndef __MARKUS_IR_QUERY__
#define __MARKUS_IR_QUERY__

#include <list>
#include <string>
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
   * Name of parameters in order.
   */
  std::vector<std::string> parameterNames;

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
  int addParameter(std::string name, Type::Container* type);

  /**
   * Returns the id of the given parameter.
   */
  int getParameterId(std::string name);

  /**
   * Returns type of the n-th parameter.
   */
  Type::Container* getParameterType(int n);

  /**
   * Returns the owner of the current query.
   */
  Program* getOwner();
};
}  // namespace IR

#endif