#include "planner/operator/scan/logical_expressions_scan.h"

namespace ladybug {
namespace planner {

void LogicalExpressionsScan::computeSchema() {
    createEmptySchema();
    schema->createGroup();
    for (auto& expression : expressions) {
        schema->insertToGroupAndScope(expression, 0);
    }
}

} // namespace planner
} // namespace ladybug
