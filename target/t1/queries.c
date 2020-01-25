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

static struct LinkedListSlot* listFront = nullptr;
static struct LinkedListSlot* listBack = nullptr;

void allProductsQueryNextHandler(struct AllProductsQueryContext* ctx) {
  if (ctx->isFinished)
    return;

  if (ctx->head == nullptr) {
    ctx->head = listFront;
    if (ctx->head == nullptr) {
      ctx->isFinished = 1;
      ctx->current = nullptr;
    } else {
      ctx->current = ctx->head->data;
    }
    return;
  }

  if ((ctx->head = ctx->head->next) == nullptr) {
    ctx->isFinished = 1;
    ctx->current = nullptr;
    return;
  }

  ctx->current = ctx->head->data;
}

struct AllProductsQueryContext* initializeAllProductsQuery(void* $$user) {
  struct AllProductsQueryContext* context = malloc(sizeof(*context));
  if (context == nullptr)
    return nullptr;
  // Common.
  context->next = &allProductsQueryNextHandler;
  context->isFinished = 0;
  context->current = nullptr;
  // State.
  context->head = nullptr;
  // Parameters.
  context->p0 = $$user;
  return context;
}

int allProductsQueryNotifyInserted(void* data) {
  if (!is(data, MARKUS_TYPE_PRODUCT))
    return -1;

  struct LinkedListSlot* slot = malloc(sizeof(*slot));
  if (slot == nullptr)
    return 0;

  slot->data = data;
  slot->next = nullptr;

  if (listBack == nullptr) {
    listFront = slot;
    listBack = slot;
  } else {
    listBack->next = slot;
    listBack = slot;
  }

  return 1;
}