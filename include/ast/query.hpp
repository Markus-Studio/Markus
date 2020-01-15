#ifndef __MARKUS_AST_QUERY__
#define __MARKUS_AST_QUERY__

#include <list>
#include <string>
#include <vector>

#include "type/container.hpp"
#include "value/call.hpp"

namespace AST {
class Program;

struct PipelineInfo {
  Type::Container* inputType;
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
   * List of pipelines in this query.
   */
  std::list<PipelineInfo> pipelines;

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
  Type::Container* getResultType();

  /**
   * Return all of the pipelines in this query.
   */
  std::vector<PipelineInfo> getPipelines();
};
}  // namespace AST

#endif