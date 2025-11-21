#pragma once

#include "common/api.h"
#include "exception.h"

namespace ladybug {
namespace common {

class KUZU_API CheckpointException : public Exception {
public:
    explicit CheckpointException(const std::exception& e) : Exception(e.what()){};
};

} // namespace common
} // namespace ladybug
