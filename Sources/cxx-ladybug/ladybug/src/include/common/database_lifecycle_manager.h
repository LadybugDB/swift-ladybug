#pragma once

namespace ladybug {
namespace common {
struct DatabaseLifeCycleManager {
    bool isDatabaseClosed = false;
    void checkDatabaseClosedOrThrow() const;
};
} // namespace common
} // namespace ladybug
