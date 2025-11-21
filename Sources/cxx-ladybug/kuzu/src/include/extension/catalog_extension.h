#pragma once

#include "catalog/catalog.h"

namespace ladybug {
namespace extension {

class LADYBUG_API CatalogExtension : public catalog::Catalog {
public:
    CatalogExtension() : Catalog() {}

    virtual void init() = 0;

    void invalidateCache();
};

} // namespace extension
} // namespace ladybug
