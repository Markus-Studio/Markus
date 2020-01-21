#ifndef __MARKUS_TYPES__
#define __MARKUS_TYPES__

/**
 * The common properties across all of the objects to use a CIS pattern.
 */
struct MarkusObjectCommon {
  /**
   * The object id.
   */
  unsigned int id;

  /**
   * Type object type.
   */
  unsigned int type;
};

/**
 * A pointer to a string in the string table.
 */
struct MarkusString {
  /**
   * The string id.
   */
  unsigned int id;

  /**
   * The string hash.
   */
  unsigned long hash;
};

enum MarkusTypeId {
  MARKUS_TYPE_GEO = 0,
  MARKUS_TYPE_PRODUCT = 1,
  MARKUS_TYPE_SELL = 2
};

// type id: 0
struct GeoObject {
  struct MarkusObjectCommon common;
  float lat;
  float lng;
};

// type id: 1
struct ProductObject {
  struct MarkusObjectCommon common;
  float price;
  struct MarkusString name;
};

// type id: 2
struct SellObject {
  struct MarkusObjectCommon common;
  struct ProductObject* product;
  unsigned long date;  // timestamp
};

void get_float_price();

#endif