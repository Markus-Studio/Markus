#include "ir/filterCollection.hpp"

namespace IR {
void FilterCollection::add(Filter filter) {
  for (int i = 0; i < filters.size(); ++i)
    if (filters[i] == filter)
      return;
  filters.push_back(filter);
}

std::vector<Filter> FilterCollection::getFilters() {
  return filters;
}

bool FilterCollection::isStatic() {
  for (int i = 0; i < filters.size(); ++i)
    if (!filters[i].isStatic())
      return false;
  return true;
}

FilterCollection FilterCollection::extractStatic() {
  FilterCollection result;
  for (int i = 0; i < filters.size(); ++i)
    if (filters[i].isStatic())
      result.add(filters[i]);
  return result;
}

FilterCollection FilterCollection::extractDynamic() {
  FilterCollection result;
  for (int i = 0; i < filters.size(); ++i)
    if (!filters[i].isStatic())
      result.add(filters[i]);
  return result;
}

bool FilterCollection::isEffecting(Type::Uri uri) {
  for (int i = 0; i < filters.size(); ++i)
    if (filters[i].isBinary() && filters[i].isEffecting(uri))
      return true;
  return false;
}

bool FilterCollection::isEmpty() {
  return filters.empty();
}
}  // namespace IR