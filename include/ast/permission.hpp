#ifndef __MARKUS_AST_PERMISSION__
#define __MARKUS_AST_PERMISSION__

#include <string>

namespace AST {
class Program;
class Query;

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
}  // namespace AST

#endif