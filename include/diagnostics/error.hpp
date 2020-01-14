#ifndef __MARKUS_DIAGNOSTICS_ERROR__
#define __MARKUS_DIAGNOSTICS_ERROR__

#include <set>
#include <string>

#include "parser/tokenizer.hpp"
#include "value/call.hpp"
#include "value/container.hpp"

namespace Diagnostics {

/**
 * All of the error numbers.
 */
enum ErrorNo {
  E_NOT_AN_ERROR,
  E_UNEXPECTED_CHARACTER,
  E_UNTERMINATED_QUOTE,
  E_UNEXPECTED_TOKEN,
  E_MISMATCHED_BRACE,
  E_EARLY_EOF,
  E_NAME_ALREADY_IN_USE,
  E_CIRCULAR_BASE,
  E_CANNOT_RESOLVE_NAME,
  E_BASE_MUST_BE_OBJECT,
  E_CIRCULAR_FIELD_IS_NOT_NULL,
  E_WRONG_NUMBER_OF_ARGUMENTS,
  E_WRONG_ARGUMENT_TYPE,
  E_VARIABLE_EXPECTED_CURRENT,
  E_FIELD_DOES_NOT_EXISTS,
  E_WRONG_INPUT_TYPE,
  E_WRONG_INPUT_SHAPE,
  E_TYPES_NOT_USEABLE_TOGETHER
};

/**
 * This class contains all of errors that can occur during
 * the execution period.
 */
class Error {
 private:
  /**
   * The unique error number indicating kind of this
   * error.
   */
  enum ErrorNo errorNo;

  /**
   * The error message.
   */
  std::string message;

  /**
   * The constructor which constructs an error, it should
   * not be used directly and one of the static factory
   * functions must be used instead.
   */
  Error(enum ErrorNo no, std::string msg);

 public:
  /**
   * Default constructor, sets the error no to E_NOT_AN_ERROR.
   */
  Error();

  /**
   * Returns the error message.
   */
  std::string getMessage();

  /**
   * Constructs a new unexpected character error.
   */
  static Error* unexpectedCharacter(int line, int column);

  /**
   * Constructs a new unterminated quote/string-literal error.
   */
  static Error* unterminatedQuote(int line, int column);

  /**
   * Construct a new unexpected token error.
   */
  static Error* unexpectedToken(Parser::Token* token);

  /**
   * Construct a new unexpected token error that also says what was expected.
   */
  static Error* unexpectedToken(Parser::Token* token, std::string expected);

  /**
   * Constructs a new mismatched brace error.
   */
  static Error* mismatchedBrace(Parser::Token* token);

  /**
   * Constructs a new early end of file error.
   */
  static Error* earlyEOF();

  /**
   * Constructs a new name already in use error.
   */
  static Error* nameAlreadyInUse(std::string name);

  /**
   * Constructs a new name already in use error from a token
   * and stating position of the error.
   */
  static Error* nameAlreadyInUse(Parser::Token* token);

  /**
   * Constructs a new circular base error.
   */
  static Error* circularBase(std::set<Parser::TokenVec*> vectors,
                             Parser::TokenVec* currnet);

  /**
   * Constructs a new base must be object error.
   */
  static Error* baseMustBeObject(Parser::Token* token);

  /**
   * Constructs a new cannot resolve name error.
   */
  static Error* cannotResolveName(Parser::Token* token);

  /**
   * Constructs a new cannot resolve name error from a call expression.
   */
  static Error* cannotResolveName(Value::Call* call);

  /**
   * Constructs a new circular field must be null.
   */
  static Error* circularField(std::string typeName, std::string fieldName);

  /**
   * Constructs a new wrong number of arguments error.
   */
  static Error* wrongNumberOfArguments(int expected, Value::Call* call);

  /**
   * Constructs a new wrong argument type error.
   */
  static Error* wrongArgumentType(enum Value::ValueKind expected,
                                  Value::Container* value);

  /**
   * Constructs a new variable expected current error.
   */
  static Error* variableExpectedCurrent(Value::Variable* value);

  /**
   * Constructs a new field does not exists error.
   */
  static Error* fieldDoesNotExists(Value::Variable* value);

  /**
   * Constructs a new wrong input type error.
   */
  static Error* wrongInputType(Value::Call* call, std::string type);

  /**
   * Constructs a new wrong input shape error.
   */
  static Error* wrongInputShape(Value::Call* call, int expected, int actual);

  /**
   * Constructs a new types not usable together error.
   */
  static Error* typesNotUseableTogether(Value::Container* lhs,
                                        Value::Container* rhs);
};
}  // namespace Diagnostics

#endif