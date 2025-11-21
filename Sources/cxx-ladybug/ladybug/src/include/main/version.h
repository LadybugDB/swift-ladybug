#pragma once
#include <cstdint>

#include "common/api.h"
namespace ladybug {
namespace main {

struct Version {
public:
    /**
     * @brief Get the version of the Ladybug library.
     * @return const char* The version of the Ladybug library.
     */
    LADYBUG_API static const char* getVersion();

    /**
     * @brief Get the storage version of the Ladybug library.
     * @return uint64_t The storage version of the Ladybug library.
     */
    LADYBUG_API static uint64_t getStorageVersion();
};
} // namespace main
} // namespace ladybug
