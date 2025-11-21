#pragma once

#include "exception.h"

namespace ladybug {
namespace common {

class LADYBUG_API ExtensionException : public Exception {
public:
    explicit ExtensionException(const std::string& msg)
        : Exception("Extension exception: " + msg) {}
};

} // namespace common
} // namespace ladybug
