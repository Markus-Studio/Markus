#ifndef __MARKUS_TYPE_CONTAINER__
#define __MARKUS_TYPE_CONTAINER__

#include <string>

namespace Type {
// Forward declaration.
class Object;
class Atomic;
class Union;
class Array;
class Uri;

enum TypeKind {
  TYPE_KIND_NEVER,
  TYPE_KIND_ATOMIC,
  TYPE_KIND_UNION,
  TYPE_KIND_OBJECT,
  TYPE_KIND_ARRAY
};

/**
 * A container is wrapper class around any other type.
 */
class Container {
 private:
  /**
   * Kind of this type.
   */
  enum TypeKind kind;

  /**
   * The type in this container.
   */
  void* type;

 public:
  /**
   * Returns the kind of type this container is containing.
   */
  enum TypeKind getKind();

  /**
   * Default constructor that contains a `never` type.
   */
  Container();

  /**
   * Returns true if the contained type is a never type.
   */
  bool isNever();

  /**
   * Construct a new container from an atomic type.
   */
  Container(Atomic* type);

  /**
   * Returns the contained type as an atomic.
   */
  Atomic* asAtomic();

  /**
   * Check if the container is containing an atomic type.
   */
  bool isAtomic();

  /**
   * Constructs a new container from an union type.
   */
  Container(Union* type);

  /**
   * Returns the contained type as an union.
   */
  Union* asUnion();

  /**
   * Check if the container is containing an union type.
   */
  bool isUnion();

  /**
   * Constructs a new container from an object type.
   */
  Container(Object* type);

  /**
   * Returns the contained type as an array.
   */
  Object* asObject();

  /**
   * Check if the container is containing an object type.
   */
  bool isObject();

  /**
   * Construct a new container from an array type.
   */
  Container(Array* type);

  /**
   * Returns the contained type as an array type.
   */
  Array* asArray();

  /**
   * Check if the container is containing an array type.
   */
  bool isArray();

  /**
   * Returns the result of `contained is type.contained`.
   */
  bool is(Container type);

  /**
   * Return the result of evaluating `contained is type`,
   * whereas type is an atomic.
   */
  bool is(Atomic* type);

  /**
   * Returns the result of evaluating `contained is type`,
   * whereas type is an union.
   */
  bool is(Union* type);

  /**
   * Return the result of evaluating `contained is type`,
   * whereas type is an object.
   */
  bool is(Object* type);

  /**
   * Return the result of evaluating `contained is type`,
   * whereas type is an array.
   */
  bool is(Array* type);

  /**
   * Returns the shape of this type.
   */
  int getShape();

  /**
   * Returns type of the field using the given uri.
   */
  Container query(Uri uri);

  /**
   * Creates and returns a new type that is sub-type of the current type and is
   * driven from the baseType.
   */
  Container extract(Container baseType);

  /**
   * Returns whatever we contain a nil type.
   */
  bool isNil();

  /**
   * Create a string representation of the type.
   */
  std::string toString();

  /**
   * Dump the type to the stdio.
   */
  void dump();
};

}  // namespace Type

#endif