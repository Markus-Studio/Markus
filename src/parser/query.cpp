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
    return nullptr;
  }

  std::string name = (iterator++)->getWord();
  AST::Query* result = new AST::Query(program);

  if (*iterator == "@") {
    ++iterator;  // Eat @
    if (*(iterator++) != "(") {
      Diagnostics::Controller::report(
          Diagnostics::Error::unexpectedToken(*iterator, "("));
      return nullptr;
    }

    // TODO(qti3e) Parse a list of permissions.

    if (!(iterator)->isIdentifier()) {
      Diagnostics::Controller::report(
          Diagnostics::Error::unexpectedToken(*iterator, "an identifier"));
      return nullptr;
    }

    std::string permissionName = iterator->getWord();
    if (!program->hasPermission(permissionName)) {
      Diagnostics::Controller::report(
          Diagnostics::Error::cannotResolveName(*iterator));
      return nullptr;
    }
    ++iterator;

    AST::Permission* permission = program->getPermission(permissionName);
    // TODO(qti3e) AST::Query must store the permissions
    // `query->allow(permission)`.
    result->addParameter("%user", permission->getQuery()->getResultType());

    if (*(iterator++) != ")") {
      Diagnostics::Controller::report(
          Diagnostics::Error::unexpectedToken(*iterator, ")"));
      return nullptr;
    }
  } else {
    result->addParameter("%user", Type::Container(program->unionOfUsers()));
  }

  if (*iterator == "(") {
    ++iterator;  // Eat (.

    while (*iterator != ")") {
      if (!(iterator)->isIdentifier()) {
        Diagnostics::Controller::report(
            Diagnostics::Error::unexpectedToken(*iterator, "an identifier"));
        return nullptr;
      }
      std::string typeName = iterator->getWord();
      if (!program->typeExists(typeName)) {
        Diagnostics::Controller::report(
            Diagnostics::Error::cannotResolveName(*iterator));
      }
      ++iterator;

      if (!(iterator)->isVariableName()) {
        Diagnostics::Controller::report(
            Diagnostics::Error::unexpectedToken(*iterator, "variable name"));
        return nullptr;
      }
      std::string parameterName = iterator->getWord();
      if (result->getParameterId(parameterName) >= 0) {
        Diagnostics::Controller::report(
            Diagnostics::Error::nameAlreadyInUse(*iterator));
        return nullptr;
      }
      ++iterator;

      result->addParameter(parameterName, program->queryType(typeName));

      if (*iterator == ",") {
        ++iterator;
      } else if (*iterator != ")") {
        Diagnostics::Controller::report(
            Diagnostics::Error::unexpectedToken(*iterator, ","));
        return nullptr;
      }
    }

    if (*(iterator++) != ")") {
      Diagnostics::Controller::report(
          Diagnostics::Error::unexpectedToken(*iterator, ")"));
      return nullptr;
    }
  }

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
        if (subQuery != nullptr) {
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

      if (arg.isNil())
        return Value::Container();

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