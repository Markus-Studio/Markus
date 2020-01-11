#include "parser/query.hpp"

#include "diagnostics/controller.hpp"

namespace Parser {
bool parseQueryBody(IR::Query* query, std::vector<Token*>::iterator& iterator) {
  if (**iterator != "{") {
    Diagnostics::Controller::report(
        Diagnostics::Error::unexpectedToken(*iterator, "{"));
    return false;
  }

  // Eat.
  ++iterator;

  // IR::Builder* fn = query->build("is");
  // fn->addParameter(...);
  // fn->addParameter(...);
  // fn->validate();
}
}  // namespace Parser