#include "main/version.h"

#include "c_api/helpers.h"
#include "c_api/ladybug.h"

char* ladybug_get_version() {
    return convertToOwnedCString(ladybug::main::Version::getVersion());
}

uint64_t ladybug_get_storage_version() {
    return ladybug::main::Version::getStorageVersion();
}
