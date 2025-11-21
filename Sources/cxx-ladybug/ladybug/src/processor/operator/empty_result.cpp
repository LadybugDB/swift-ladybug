#include "processor/operator/empty_result.h"

namespace ladybug {
namespace processor {

bool EmptyResult::getNextTuplesInternal(ExecutionContext*) {
    return false;
}

} // namespace processor
} // namespace ladybug
