#pragma once

#include "common/api.h"
#include "exception.h"

namespace ladybug {
namespace common {

class KUZU_API CatalogException : public Exception {
public:
    explicit CatalogException(const std::string& msg) : Exception("Catalog exception: " + msg){};
};

} // namespace common
} // namespace ladybug
