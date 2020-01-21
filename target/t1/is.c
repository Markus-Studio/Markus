#include "is.h"

// clang-format off
static const char markus_is_lookup_matrix[3][3] = {
  1, 0, 0,
  0, 1, 0,
  0, 0, 1
};
// clang-format on

int is(void* data, enum MarkusTypeId type) {
  return markus_is_lookup_matrix[((struct MarkusObjectCommon*)data)->type]
                                [type];
}