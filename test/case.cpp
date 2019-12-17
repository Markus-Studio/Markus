#include "test.hpp"

void test_01(struct MarkusTesting::TestContext* ctx) {}

namespace {
MarkusTesting::AutoReg x("Test 01", &test_01);
}

void test_2(struct MarkusTesting::TestContext* ctx) {
  ctx->failed = true;
}

namespace {
MarkusTesting::AutoReg y("Test 02", &test_2);
}