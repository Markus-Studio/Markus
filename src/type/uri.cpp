#include "type/uri.hpp"

#include <string>
#include <vector>

namespace Type {
Uri::Uri() {}

Uri::Uri(std::vector<std::string> units) {
  this->units.assign(units.begin(), units.end());
}

Uri::Uri(std::string unit) {
  units.push_back(unit);
}

Uri::Uri(std::string u1, std::string u2) {
  units.push_back(u1);
  units.push_back(u2);
}

Uri::Uri(std::string u1, std::string u2, std::string u3) {
  units.push_back(u1);
  units.push_back(u2);
  units.push_back(u3);
}

bool Uri::isEmpty() {
  return units.empty();
}

Uri Uri::popFirst() {
  Uri temp;
  temp.units.assign(units.begin() + 1, units.end());
  return temp;
}

Uri Uri::prepend(Uri uri) {
  Uri temp = uri;
  temp.units.insert(temp.units.end(), units.begin(), units.end());
  return temp;
}

Uri Uri::prepend(std::string part) {
  Uri temp;
  temp.units.push_back(part);
  temp.units.insert(temp.units.end(), units.begin(), units.end());
  return temp;
}

std::vector<std::string> Uri::getUnits() {
  return units;
}

std::string Uri::getFirstUnit() {
  return units[0];
}

int Uri::size() {
  return units.size();
}

bool Uri::operator==(Type::Uri uri) {
  return units == uri.units;
}
}  // namespace Type