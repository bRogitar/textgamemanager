#include "BaseMonster.h"

BaseMonster::BaseMonster(const std::string& name, int health, int attackPower)
    : name(name), health(health), attackPower(attackPower), combatHealth(health) {}

void BaseMonster::setCombatHealth(int health) {
    combatHealth = health;
}

int BaseMonster::getCombatHealth() const {
    return combatHealth;
}

void BaseMonster::takeCombatDamage(int damage) {
    combatHealth -= damage;
    if (combatHealth < 0) {
        combatHealth = 0;
    }
}

bool BaseMonster::isCombatDefeated() const {
    return combatHealth <= 0;
}

std::string BaseMonster::getName() const {
    return name;
}

int BaseMonster::getHealth() const {
    return health;
}

int BaseMonster::getAttackPower() const {
    return attackPower;
}
