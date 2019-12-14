#ifndef __MARKUS_TYPE_URI__
#define __MARKUS_TYPE_URI__

#include <vector>
#include <iterator>
#include <string>

namespace Type
{

/**
 * A URI object represents the field address that can be resolved
 * to a type on an object.
 * 
 * For example: a.x -> uri = Uri("a", "x");
 * and then we can use it like: objectType.set(uri, type);
 */
class Uri
{
private:
    /**
     * URI units that are string.
     */
    std::vector<std::string> units;

public:
    /**
     * Constructs an empty URI.
     */
    Uri();

    /**
     * Constructs a new URI with the given units.
     */
    Uri(std::vector<std::string> units);

    /**
     * Constructs a new URI which has only one unit which is passed as the
     * first argument.
     */
    Uri(std::string unit);

    /**
     * Constructs new URI which has two units which are passed as arguments.
     */
    Uri(std::string unit, std::string unit2);

    /**
     * Constructs new URI which has 3 units which are passed as arguments.
     */
    Uri(std::string unit, std::string unit2, std::string unit3);

    /**
     * Returns true if this URI has no units and is empty.
     */
    bool isEmpty();

    /**
     * Pops the first element from the units and return a new URI.
     */
    Uri popFirst();

    /**
     * Returns an iterator over units.
     */
    std::vector<std::string> getUnits();

    /**
     * Returns the first unit.
     */
    std::string getFirstUnit();

    /**
     * Number of units in this uri.
     */
    int size();
};
} // namespace Type

#endif