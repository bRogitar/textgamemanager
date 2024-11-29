
// ItemInventory.cpp
#include "../ItemInventory.h"
#include <algorithm>

void ItemInventory::addItem(const Item& item) {
    items.push_back(item);
}

void ItemInventory::removeItem(const Item& item) {
    auto it = std::remove_if(items.begin(), items.end(),
        [&item](const Item& i) { return i.itemId == item.itemId; });
    if (it != items.end()) {
        items.erase(it, items.end());
    }
}

bool ItemInventory::hasItem(const std::string& itemId) const {
    return std::any_of(items.begin(), items.end(),
        [&itemId](const Item& i) { return i.itemId == itemId; });
}
