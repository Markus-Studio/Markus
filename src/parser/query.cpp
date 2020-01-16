#include "parser/query.hpp"

#include "ast/source.hpp"
#include "diagnostics/controller.hpp"
#include "parser/range.hpp"

namespace Parser {
AST::Query* parseQuery(AST::Source* program, TokenVec tokens) {
  std::vector<Token>::iterator iterator = tokens.begin();
  assert(*iterator == "query");

  ++iterator;

  if (!(iterator)->isIdentifier()) {
    Diagnostics::Controller::report(
        Diagnostics::Error::unexpectedToken(*iterator, "an identifier"));
    return NULL;
  }

  std::string name = (iterator++)->getWord();
  AST::Query* result = new AST::Query(program);

  // TODO(qti3e) Parse the permission section.
  result->addParameter("%user", Type::Container(program->unionOfUsers()));

  parseQueryBody(result, iterator);

  return result;
}

bool parseQueryBody(AST::Query* query, std::vector<Token>::iterator& iterator) {
  if (*iterator != "{") {
    Diagnostics::Controller::report(
        Diagnostics::Error::unexpectedToken(*iterator, "{"));
    return false;
  }

  // Eat {.
  ++iterator;

  while (*iterator != "}") {
    Value::Container c = parseValue(query, iterator);

    // TODO(qti3e)
    //    if (c == NULL)
    //      return false;

    if (!c.isCall())
      return false;

    if (!query->addPipeline(c.asCall()))
      return false;

    if (*iterator == "}")
      break;

    if (*iterator != ",") {
      Diagnostics::Controller::report(
          Diagnostics::Error::unexpectedToken(*iterator, ","));
      return false;
    }

    ++iterator;
  }

  ++iterator;  // Eat }

  return true;
}

Value::Container parseValue(AST::Query* query,
                            std::vector<Token>::iterator& token) {
  if ((token)->isBoolLiteral()) {
    return Value::Container(new Value::Bool(*(token++)));
  }

  if ((token)->isFloatLiteral()) {
    return Value::Container(new Value::Float(*(token++)));
  }

  if ((token)->isIntLiteral()) {
    return Value::Container(new Value::Int(*(token++)));
  }

  if ((token)->isStringLiteral()) {
    return Value::Container(new Value::String(*(token++)));
  }

  if (*token == "." && ((token + 1))->isIdentifierWord()) {
    return Value::Container(parseVariable(query, token, 0));
  }

  if ((token)->isVariableName() || (token)->isInternalVariableName()) {
    Token* name = &*(token++);
    int variableId = query->getParameterId(name->getWord());
    return Value::Container(parseVariable(query, token, variableId));
  }

  if ((token)->isIdentifier()) {
    Token name = *(token++);

    if (*token != "(") {
      if (!query->getOwner()->hasType(name.getWord())) {
        Diagnostics::Controller::report(
            Diagnostics::Error::cannotResolveName(name));
        return Value::Container();
      }

      return Value::Container(new Value::TypeValue(
          Type::Container(query->getOwner()->getType(name.getWord())),
          Range::fromToken(name)));
    }

    token++;  // Eat "("
    Value::Call* call = new Value::Call(name);

    while (*token != ")") {
      if (*token == "}") {
        Diagnostics::Controller::report(
            Diagnostics::Error::unexpectedToken(*token, ")"));
        return Value::Container();
      }

      Value::Container arg;

      if (*token == "{") {
        AST::Query* subQuery = query->getSubQuery(call);
        if (subQuery != NULL) {
          arg = Value::Container(subQuery);
          parseQueryBody(subQuery, token);
        } else {
          Diagnostics::Controller::report(
              Diagnostics::Error::unexpectedToken(*token));
          return Value::Container();
        }
      } else {
        arg = parseValue(query, token);
      }

      // TODO(qti3e)
      // if (arg == NULL)
      // return NULL;

      call->addArgument(arg);

      if (*token == ")") {
        call->expandRange(Range::fromToken(*token));
        break;
      }

      if (*token != ",") {
        Diagnostics::Controller::report(
            Diagnostics::Error::unexpectedToken(*token, ","));
        return Value::Container();
      }

      ++token;
    }

    if (*token == ")")
      token++;

    return Value::Container(call);
  }

  Diagnostics::Controller::report(Diagnostics::Error::unexpectedToken(*token));
  return Value::Container();
}

Value::Variable* parseVariable(AST::Query* query,
                               std::vector<Token>::iterator& token,
                               int variableId) {
  std::vector<std::string> uriParts;
  Range range = Range::fromToken(*(token - (variableId == 0 ? 0 : 1)));

  while (*token == ".") {
    if (!((token + 1))->isIdentifierWord())
      break;

    token++;
    range = range + Range::fromToken(*token);
    uriParts.push_back(((token++))->getWord());
  }

  if (uriParts.size() == 0)
    return new Value::Variable(variableId, query->getParameterType(variableId),
                               range);

  return new Value::Variable(variableId, query->getParameterType(variableId),
                             range, new Type::Uri(uriParts));
}

}  // namespace Parser