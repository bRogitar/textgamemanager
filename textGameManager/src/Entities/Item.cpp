// Item.cpp
#include "Item.h"
#include "PlayerStatus.h"
#include <iostream>

Item::Item(const std::string& itemId, const std::string& name, const std::string& description, bool isConsumable)
    : itemId(itemId), name(name), description(description), isConsumable(isConsumable) {}

void Item::addEffect(const std::string& stat, int value) {
    effects[stat] = value;
}

void Item::use(PlayerStatus& playerStatus) const {
    for (const auto& effect : effects) {
        if (effect.first == "health") {
            playerStatus.modifyHealth(effect.second);
        } else if (effect.first == "mental") {
            playerStatus.modifyMentalStrength(effect.second);
        }
    }
    std::cout << "Used item: " << name << "\n";
}

std::string Item::getItemId() const {
    return itemId;
}

std::string Item::getName() const {
    return name;
}

std::string Item::getDescription() const {
    return description;
}
