#pragma once

#include "common/api.h"
#include "exception.h"

namespace ladybug {
namespace common {

class LADYBUG_API InterruptException : public Exception {
public:
    explicit InterruptException() : Exception("Interrupted."){};
};

} // namespace common
} // namespace ladybug
