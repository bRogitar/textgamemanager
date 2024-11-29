#include "ItemFactory.h"

std::unique_ptr<Item> ItemFactory::createItem(const std::string& type) {
    if (type == "HealthPotion") {
        auto item = std::make_unique<Item>("health_potion", "Health Potion", "Restores 50 health.", true);
        item->addEffect("health", 50);
        return item;
    } else if (type == "MentalPotion") {
        auto item = std::make_unique<Item>("mental_potion", "Mental Potion", "Restores 30 mental strength.", true);
        item->addEffect("mental", 30);
        return item;
    }
    return nullptr;
} 