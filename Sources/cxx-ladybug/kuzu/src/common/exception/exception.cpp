#include "common/exception/exception.h"

#ifdef LADYBUG_BACKTRACE
#include <cpptrace/cpptrace.hpp>
#endif

namespace ladybug {
namespace common {

Exception::Exception(std::string msg) : exception(), exception_message_(std::move(msg)) {
#ifdef LADYBUG_BACKTRACE
    cpptrace::generate_trace(1 /*skip this function's frame*/).print();
#endif
}

} // namespace common
} // namespace ladybug
