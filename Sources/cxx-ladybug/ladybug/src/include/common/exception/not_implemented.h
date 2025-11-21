#pragma once

#include "common/api.h"
#include "exception.h"

namespace ladybug {
namespace common {

class LADYBUG_API NotImplementedException : public Exception {
public:
    explicit NotImplementedException(const std::string& msg) : Exception(msg){};
};

} // namespace common
} // namespace ladybug
