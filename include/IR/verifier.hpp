#ifndef __MARKUS_IR_VERIFIER__
#define __MARKUS_IR_VERIFIER__

#include "value/call.hpp"

namespace IR {
class Query;

bool verifyCall(Query* query, Value::Call* call);
}  // namespace IR

#endif