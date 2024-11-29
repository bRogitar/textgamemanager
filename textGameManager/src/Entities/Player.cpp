// Player.cpp
#include <algorithm> // Added to resolve std::find usage
#include "Player.h"
#include <iostream> // For console output in applyDefeatPenalty

Player::Player(const std::string& name, int health, int mentalStrength, int attackPower, int money)
    : name(name), health(health), mentalStrength(mentalStrength), attackPower(attackPower), money(money), combatHealth(health), itemInventory(), abilityInventory() {}

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

bool Player::isDefeated() const {
    return health <= 0; // 추가된 멤버 함수 구현
}

void Player::takeDamage(int damage) {
    modifyHealth(-damage);
    if (health < 0) {
        health = 0;
    }
}

void Player::applyDefeatPenalty() {
    // 패배 시 체력과 정신력 감소
    int healthPenalty = 10;
    int mentalStrengthPenalty = 5;

    modifyHealth(-healthPenalty);
    modifyMentalStrength(-mentalStrengthPenalty);

    std::cout << "You have been defeated. Health reduced by " << healthPenalty
              << ", Mental Strength reduced by " << mentalStrengthPenalty << ".\n";
}

void Player::setCombatHealth(int health) {
    combatHealth = health;
}

int Player::getCombatHealth() const {
    return combatHealth;
}

void Player::modifyCombatHealth(int amount) {
    combatHealth += amount;
    if (combatHealth < 0) {
        combatHealth = 0;
    }
}

bool Player::isCombatDefeated() const {
    return combatHealth <= 0;
}

void Player::takeCombatDamage(int damage) {
    combatHealth -= damage;
    if (combatHealth < 0) {
        combatHealth = 0;
    }
}