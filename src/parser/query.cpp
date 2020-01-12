#include "parser/query.hpp"

#include "diagnostics/controller.hpp"
#include "value/container.hpp"

namespace Parser {
inline Value::Variable* parseVariable(IR::Query* query,
                                      std::vector<Token*>::iterator& token,
                                      int variableId);

Value::Container* parseValue(IR::Query* query,
                             std::vector<Token*>::iterator& token);
bool parseQueryBody(IR::Query* query, std::vector<Token*>::iterator& iterator) {
  if (**iterator != "{") {
    Diagnostics::Controller::report(
        Diagnostics::Error::unexpectedToken(*iterator, "{"));
    return false;
  }

  // Eat.
  ++iterator;

  while (**iterator != "}") {
    Value::Container* c = parseValue(query, iterator);

    if (c == NULL)
      return false;

    if (!c->isCall())
      return false;

    if (!query->addPipeline(c->asCall()))
      return false;

    if (**iterator == "}") {
      break;
    }

    if (**iterator != ",") {
      Diagnostics::Controller::report(
          Diagnostics::Error::unexpectedToken(*iterator, ","));
      return false;
    }

    ++iterator;
  }

  return true;
}

Value::Container* parseValue(IR::Query* query,
                             std::vector<Token*>::iterator& token) {
  if ((*token)->isBoolLiteral()) {
    return new Value::Container(new Value::Bool(((*token++))->getWord()));
  }

  if ((*token)->isFloatLiteral()) {
    return new Value::Container(new Value::Float((*(token++))->getWord()));
  }

  if ((*token)->isIntLiteral()) {
    return new Value::Container(new Value::Int((*(token++))->getWord()));
  }

  if ((*token)->isStringLiteral()) {
    return new Value::Container(new Value::String((*(token++))->getWord()));
  }

  if (**token == "." && (*(token + 1))->isIdentifierWord()) {
    return new Value::Container(parseVariable(query, token, 0));
  }

  if ((*token)->isVariableName() || (*token)->isInternalVariableName()) {
    Token* name = *(token++);
    int variableId = query->getParameterId(name->getWord());
    return new Value::Container(parseVariable(query, token, variableId));
  }

  if ((*token)->isIdentifier()) {
    Token* name = *(token++);

    if (**token != "(") {
      if (!query->getOwner()->hasType(name->getWord())) {
        Diagnostics::Controller::report(
            Diagnostics::Error::cannotResolveName(name));
        return NULL;
      }

      return new Value::Container(new Value::TypeValue(
          new Type::Container(query->getOwner()->getType(name->getWord()))));
    }

    token++;  // Eat "("
    Value::Call* call = new Value::Call(name->getWord());

    while (**token != ")") {
      if (**token == "}") {
        Diagnostics::Controller::report(
            Diagnostics::Error::unexpectedToken(*token, ")"));
        return NULL;
      }

      Value::Container* arg = parseValue(query, token);
      if (arg == NULL) {
        Diagnostics::Controller::report(
            Diagnostics::Error::unexpectedToken(*token));
        return NULL;
      }

      call->addArgument(arg);

      if (**token == ")") {
        ++token;
        break;
      }

      if (**token != ",") {
        Diagnostics::Controller::report(
            Diagnostics::Error::unexpectedToken(*token, ","));
        return NULL;
      }

      ++token;
    }

    return new Value::Container(call);
  }

  return NULL;
}

inline Value::Variable* parseVariable(IR::Query* query,
                                      std::vector<Token*>::iterator& token,
                                      int variableId) {
  std::vector<std::string> uriParts;

  while (**token == ".") {
    if (!(*(token + 1))->isIdentifierWord())
      break;

    token++;
    uriParts.push_back((*(token++))->getWord());
  }

  if (uriParts.size() == 0)
    return new Value::Variable(variableId, query->getParameterType(variableId));

  return new Value::Variable(variableId, query->getParameterType(variableId),
                             new Type::Uri(uriParts));
}

}  // namespace Parser