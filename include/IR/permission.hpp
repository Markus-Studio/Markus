#ifndef __MARKUS_IR_PERMISSION__
#define __MARKUS_IR_PERMISSION__

#include <string>

#include "IR/program.hpp"
#include "IR/query.hpp"

namespace IR {
class Permission {
 private:
  /**
   * Name of this permission.
   */
  std::string name;

  /**
   * The query for this permission.
   */
  Query* query;

 public:
  /**
   * Constructs a new permission.
   */
  Permission(Program* program, std::string name);

  /**
   * Return the name of this permission declaration.
   */
  std::string getName();

  /**
   * Return the query.
   */
  Query* getQuery();
};
}  // namespace IR

#endif