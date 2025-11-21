#include "planner/operator/logical_dummy_sink.h"

namespace ladybug {
namespace planner {

void LogicalDummySink::computeFactorizedSchema() {
    copyChildSchema(0);
}

void LogicalDummySink::computeFlatSchema() {
    copyChildSchema(0);
}

} // namespace planner
} // namespace ladybug
