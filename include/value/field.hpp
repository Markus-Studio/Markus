#ifndef __MARKUS_VALUE_FIELD__
#define __MARKUS_VALUE_FIELD__

#include <string>
#include "type/uri.hpp"

namespace Value
{
/**
 * The field value is just a URI with informations regarding
 * its location in the source code.
 */
class Field
{
private:
    /**
     * The URI for this value.
     */
    Type::Uri uri;

    /**
     * Line number.
     */
    int line;

    /**
     * Column number.
     */
    int column;

public:
    /**
     * Constructs a new Field value.
     */
    Field(int line, int column, Type::Uri uri);

    /**
     * Return the uri.
     */
    Type::Uri asUri();

    /**
     * Return the line number.
     */
    int getLine();

    /**
     * Return the column number.
     */
    int getColumn();

    /**
     * Format the field and return it as an string.
     */
    std::string toString();
};
} // namespace Value

#endif