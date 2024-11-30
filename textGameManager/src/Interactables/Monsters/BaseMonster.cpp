#include "BaseMonster.h"

BaseMonster::BaseMonster(const std::string& name, int health, int attackPower)
    : name(name), health(health), attackPower(attackPower), combatHealth(health) {}

std::string BaseMonster::getName() const {
    return name;
}

int BaseMonster::getHealth() const {
    return health;
}

int BaseMonster::getAttackPower() const {
    return attackPower;
}

void BaseMonster::setCombatHealth(int newHealth) {
    combatHealth = newHealth;
}

int BaseMonster::getCombatHealth() const {
    return combatHealth;
}

bool BaseMonster::isCombatDefeated() const {
    return combatHealth <= 0;
}

void BaseMonster::takeCombatDamage(int damage) {
    combatHealth -= damage;
    if (combatHealth < 0) {
        combatHealth = 0;
    }
}
