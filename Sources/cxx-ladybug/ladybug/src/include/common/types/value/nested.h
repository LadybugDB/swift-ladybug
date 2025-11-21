#pragma once

#include <cstdint>

#include "common/api.h"

namespace ladybug {
namespace common {

class Value;

class NestedVal {
public:
    LADYBUG_API static uint32_t getChildrenSize(const Value* val);

    LADYBUG_API static Value* getChildVal(const Value* val, uint32_t idx);
};

} // namespace common
} // namespace ladybug
