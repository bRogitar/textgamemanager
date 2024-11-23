#include <algorithm> // Added to resolve std::find usage
#include "Player.h"

Player::Player(const std::string& name, int health, int mentalStrength, int attackPower, int money)
    : name(name), health(health), mentalStrength(mentalStrength), attackPower(attackPower), money(money), itemInventory(), abilityInventory() {}

void Player::setName(const std::string& name) {
    this->name = name;
}

std::string Player::getName() const {
    return name;
}

void Player::setHealth(int health) {
    this->health = health;
}

int Player::getHealth() const {
    return health;
}

void Player::setMentalStrength(int mentalStrength) {
    this->mentalStrength = mentalStrength;
}

int Player::getMentalStrength() const {
    return mentalStrength;
}

void Player::setAttackPower(int attackPower) {
    this->attackPower = attackPower;
}

int Player::getAttackPower() const {
    return attackPower;
}

void Player::setMoney(int money) {
    this->money = money;
}

int Player::getMoney() const {
    return money;
}

void Player::modifyHealth(int amount) {
    setHealth(getHealth() + amount);
    if (getHealth() < 0) {
        setHealth(0);
    }
}

void Player::modifyMentalStrength(int amount) {
    setMentalStrength(getMentalStrength() + amount);
    if (getMentalStrength() < 0) {
        setMentalStrength(0);
    }
}

void Player::modifyAttackPower(int amount) {
    setAttackPower(getAttackPower() + amount);
    if (getAttackPower() < 0) {
        setAttackPower(0);
    }
}

void Player::modifyMoney(int amount) {
    setMoney(getMoney() + amount);
    if (getMoney() < 0) {
        setMoney(0);
    }
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
