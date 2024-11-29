// Item.cpp
#include "BaseItem.h"
#include <iostream>
#include "Player.h"

Item::Item(const std::string& itemId, const std::string& name, const std::string& description, bool isConsumable)
    : itemId(itemId), name(name), description(description), isConsumable(isConsumable) {}

void Item::addEffect(const std::string& stat, int value) {
    effects[stat] = value;
}

void Item::use(Player& player) const {
    for (const auto& effect : effects) {
        if (effect.first == "health") {
            player.modifyHealth(effect.second);
        } else if (effect.first == "mental") {
            player.modifyMentalStrength(effect.second);
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
