// Player.cpp
#include "Player.h"
#include <algorithm> // Added to resolve std::find usage

Player::Player() : name("Player"), status(), itemInventory(), abilityInventory() {}

Player::Player(const std::string& name, int strength, int health)
    : name(name), status(), itemInventory(), abilityInventory() {
    status.modifyHealth(health - 100); // Adjust initial health
}

void Player::modifyHealth(int amount) {
    status.modifyHealth(amount);
}

void Player::addItem(const Item& item) {
    itemInventory.addItem(item);
}

void Player::removeItem(const Item& item) {
    itemInventory.removeItem(item);
}

bool Player::hasItem(const std::string& itemId) const {
    return itemInventory.hasItem(itemId);
}

void Player::addAbility(const Ability& ability) {
    abilityInventory.addAbility(ability);
}

void Player::removeAbility(const Ability& ability) {
    abilityInventory.removeAbility(ability);
}

bool Player::hasAbility(const std::string& abilityId) const {
    return abilityInventory.hasAbility(abilityId);
}