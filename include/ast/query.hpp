#ifndef __MARKUS_AST_QUERY__
#define __MARKUS_AST_QUERY__

#include <list>
#include <string>
#include <vector>

#include "type/container.hpp"
#include "value/call.hpp"

namespace AST {
class Source;

struct PipelineInfo {
  Type::Container inputType;
  int shape;
  Value::Call* call;
};

/**
 * The intermediate representation for any query in the system.
 */
class Query {
  /**
   * Every query belongs to a program.
   */
  Source* owner;

  /**
   * The return type of this query.
   */
  Type::Container resultType;

  /**
   * Type of parameters.
   */
  std::vector<Type::Container> parameters;

  /**
   * Name of parameters in order.
   */
  std::vector<std::string> parameterNames;

  /**
   * List of pipelines in this query.
   */
  std::list<PipelineInfo> pipelines;

 public:
  /**
   * Constructs a new Query AST Node.
   */
  Query(Source* program);

  /**
   * Constructs a new Query AST Node with the intialized type.
   */
  Query(Source* program, Type::Container type);

  /**
   * Add a new parameter to this query, returns the parameter id.
   */
  int addParameter(std::string name, Type::Container type);

  /**
   * Returns the id of the given parameter.
   */
  int getParameterId(std::string name);

  /**
   * Returns type of the n-th parameter.
   */
  Type::Container getParameterType(int n);

  /**
   * Returns the owner of the current query.
   */
  Source* getOwner();

  /**
   * Add the given pipeline to this query.
   */
  bool addPipeline(Value::Call* call);

  /**
   * Return the sub query to be used as an argument for the call.
   * (Of course the call is not completely parsed when it's passed
   * to this method.)
   */
  Query* getSubQuery(Value::Call* call);

  /**
   * Returns the result type of this query.
   */
  Type::Container getResultType();

  /**
   * Return all of the pipelines in this query.
   */
  std::vector<PipelineInfo> getPipelines();
};
}  // namespace AST

#endif