#pragma once

#include "common/api.h"
#include "exception.h"

namespace ladybug {
namespace common {

class LADYBUG_API ConversionException : public Exception {
public:
    explicit ConversionException(const std::string& msg)
        : Exception("Conversion exception: " + msg) {}
};

} // namespace common
} // namespace ladybug
