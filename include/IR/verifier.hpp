#ifndef __MARKUS_IR_VERIFIER__
#define __MARKUS_IR_VERIFIER__

#include "type/container.hpp"
#include "value/call.hpp"

namespace IR {
class Query;

bool verifyCall(Query* query, Value::Call* call, Type::Container*& resultType);
}  // namespace IR

#endif