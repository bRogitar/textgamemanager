#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <memory>
#include "Item.h"

class ItemFactory {
public:
    static std::unique_ptr<Item> createItem(const std::string& type);
};

#endif // ITEMFACTORY_H 