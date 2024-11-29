// ItemInventory.h
#ifndef ITEMINVENTORY_H
#define ITEMINVENTORY_H

#include <vector>
#include <string>
#include "Item.h"

class ItemInventory {
public:
    void addItem(const Item& item);
    void removeItem(const Item& item);
    bool hasItem(const std::string& itemId) const;

private:
    std::vector<Item> items;
};

#endif // ITEMINVENTORY_H