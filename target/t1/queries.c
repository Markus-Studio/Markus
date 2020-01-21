#include <stdlib.h>

#include "is.h"
#include "types.h"

struct LinkedListSlot {
  void* data;
  struct LinkedListSlot* next;
};

struct AllProductsQueryContext {
  void (*next)(struct AllProductsQueryContext*);
  int isFinished;
  void* current;  // Type: Product
  // --- STATE ---
  struct LinkedListSlot* head;
  // --- PARAMETERS ---
  void* p0;  // User
};

static struct LinkedListSlot* listFront = NULL;
static struct LinkedListSlot* listBack = NULL;

void allProductsQueryNextHandler(struct AllProductsQueryContext* ctx) {
  if (ctx->isFinished)
    return;

  if (ctx->head == NULL) {
    ctx->head = listFront;
    if (ctx->head == NULL) {
      ctx->isFinished = 1;
      ctx->current = NULL;
    } else {
      ctx->current = ctx->head->data;
    }
    return;
  }

  if ((ctx->head = ctx->head->next) == NULL) {
    ctx->isFinished = 1;
    ctx->current = NULL;
    return;
  }

  ctx->current = ctx->head->data;
}

struct AllProductsQueryContext* initializeAllProductsQuery(void* $$user) {
  struct AllProductsQueryContext* context = malloc(sizeof(*context));
  if (context == NULL)
    return NULL;
  // Common.
  context->next = &allProductsQueryNextHandler;
  context->isFinished = 0;
  context->current = NULL;
  // State.
  context->head = NULL;
  // Parameters.
  context->p0 = $$user;
  return context;
}

int allProductsQueryNotifyInserted(void* data) {
  if (!is(data, MARKUS_TYPE_PRODUCT))
    return -1;

  struct LinkedListSlot* slot = malloc(sizeof(*slot));
  if (slot == NULL)
    return 0;

  slot->data = data;
  slot->next = NULL;

  if (listBack == NULL) {
    listFront = slot;
    listBack = slot;
  } else {
    listBack->next = slot;
    listBack = slot;
  }

  return 1;
}