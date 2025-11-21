#pragma once

#include "common/api.h"
#include "exception.h"

namespace ladybug {
namespace common {

class LADYBUG_API BinderException : public Exception {
public:
    explicit BinderException(const std::string& msg) : Exception("Binder exception: " + msg){};
};

} // namespace common
} // namespace ladybug
