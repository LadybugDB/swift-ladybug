#include "function/function.h"

#include "binder/expression/expression_util.h"

using namespace ladybug::binder;
using namespace ladybug::common;

namespace ladybug {
namespace function {

std::unique_ptr<FunctionBindData> FunctionBindData::getSimpleBindData(
    const expression_vector& params, const LogicalType& resultType) {
    auto paramTypes = ExpressionUtil::getDataTypes(params);
    return std::make_unique<FunctionBindData>(std::move(paramTypes), resultType.copy());
}

} // namespace function
} // namespace ladybug
