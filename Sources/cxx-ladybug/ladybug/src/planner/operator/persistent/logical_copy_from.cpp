#include "planner/operator/persistent/logical_copy_from.h"

using namespace ladybug::common;

namespace ladybug {
namespace planner {

void LogicalCopyFrom::computeFactorizedSchema() {
    copyChildSchema(0);
}

void LogicalCopyFrom::computeFlatSchema() {
    copyChildSchema(0);
}

} // namespace planner
} // namespace ladybug
