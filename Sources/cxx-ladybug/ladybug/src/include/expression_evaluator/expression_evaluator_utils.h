#pragma once

#include "binder/expression/expression.h"
#include "common/types/value/value.h"
#include "main/client_context.h"

namespace ladybug {
namespace evaluator {

struct ExpressionEvaluatorUtils {
    static LADYBUG_API common::Value evaluateConstantExpression(
        std::shared_ptr<binder::Expression> expression, main::ClientContext* clientContext);
};

} // namespace evaluator
} // namespace ladybug
