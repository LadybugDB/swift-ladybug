#include "planner/operator/logical_flatten.h"

using namespace ladybug::common;

namespace ladybug {
namespace planner {

void LogicalFlatten::computeFactorizedSchema() {
    copyChildSchema(0);
    schema->flattenGroup(groupPos);
}

void LogicalFlatten::computeFlatSchema() {
    throw InternalException("LogicalFlatten::computeFlatSchema() should never be used.");
}

} // namespace planner
} // namespace ladybug
