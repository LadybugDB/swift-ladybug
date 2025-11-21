#include "processor/operator/empty_result.h"
#include "processor/plan_mapper.h"

using namespace ladybug::planner;

namespace ladybug {
namespace processor {

std::unique_ptr<PhysicalOperator> PlanMapper::mapEmptyResult(const LogicalOperator*) {
    auto printInfo = std::make_unique<OPPrintInfo>();
    return std::make_unique<EmptyResult>(getOperatorID(), std::move(printInfo));
}

} // namespace processor
} // namespace ladybug
