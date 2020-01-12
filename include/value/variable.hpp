#ifndef __MARKUS_VALUE__VARIABLE__
#define __MARKUS_VALUE__VARIABLE__

#include "parser/range.hpp"
#include "type/container.hpp"
#include "type/uri.hpp"

namespace Value {
/**
 * A reference to a variable, either internal or parameter.
 */
class Variable {
 private:
  /**
   * Type of the base.
   */
  Type::Container* variableType;

  /**
   * The parameter id for this variable.
   */
  int variableId;

  /**
   * If there is a member selection on this variable.
   */
  bool hasVariableMember;

  /**
   * The selected member from the base if any.
   */
  Type::Uri* variableMember;

  /**
   * Cache of the getType().
   */
  Type::Container* typeCache;

  /**
   * The source code range that contains this value.
   */
  Parser::Range range;

 public:
  /**
   * Constructs a new reference to a variable.
   */
  Variable(int id, Type::Container* type, Parser::Range range);

  /**
   * Constructs a new reference to a variable with a member selection.
   */
  Variable(int id,
           Type::Container* type,
           Parser::Range range,
           Type::Uri* member);

  /**
   * Returns true if there is a member selected on this variable.
   */
  bool hasMember();

  /**
   * Returns the type of the base, without considering selected member.
   * $point.x -> Point2D
   */
  Type::Container* getBaseType();

  /**
   * Returns the type of this entity, considers the selected member.
   * $point.x -> float
   */
  Type::Container* getType();

  /**
   * Returns uri of the selected member.
   */
  Type::Uri* getMember();

  /**
   * Returns the variable id.
   */
  int getId();

  /**
   * Returns the range which this value is derived from in the source code.
   */
  Parser::Range getRange();
};
}  // namespace Value

#endif