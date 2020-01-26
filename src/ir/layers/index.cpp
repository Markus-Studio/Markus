#include "ir/layers/index.hpp"

#include <sstream>

namespace IR {
namespace Layers {
bool Index::addFilter(Filter filter) {
  // TODO(qti3e)
  return false;
}

FilterCollection Index::getFunction() {
  return function;
}

bool Index::isFunctionEmpty() {
  return function.isEmpty();
}

std::string Index::toString() {
  std::stringstream stream;
  std::vector<Filter> filters = function.getFilters();

  stream << "Index {" << std::endl;
  stream << "  function: Filter {" << std::endl;
  for (int i = 0; i < filters.size(); ++i)
    stream << "    " << filters[i].toString() << std::endl;
  stream << "  }" << std::endl;
  stream << "}";
  return stream.str();
}
}  // namespace Layers
}  // namespace IR