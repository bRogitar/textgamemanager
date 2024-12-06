#include "BaseMonster.h"
#include <iostream>

// 생성자 구현
BaseMonster::BaseMonster(const std::string& name, int health, int attackPower)
    : name(name), health(health), attackPower(attackPower) {}

// Getter 메서드 구현
const std::string& BaseMonster::getName() const {
    return name;
}

int BaseMonster::getHealth() const {
    return health;
}

int BaseMonster::getAttackPower() const {
    return attackPower;
}

// 전투 관련 메서드 구현
void BaseMonster::setHealth(int newHealth) {
    health = newHealth;
}

bool BaseMonster::isCombatDefeated() const {
    return health <= 0;
}

void BaseMonster::takeCombatDamage(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0; // 체력은 음수가 될 수 없음
    }
}

// 새로운 setAttributes 메서드 구현
void BaseMonster::setAttributes(const std::string& newName, int newHealth, int newAttackPower) {
    name = newName;
    health = newHealth;
    attackPower = newAttackPower;
}

// 상태 출력 메서드 구현
void BaseMonster::displayStatus() const {
    std::cout << "Monster: " << name << ", Health: " << health << ", Attack Power: " << attackPower << std::endl;
}
