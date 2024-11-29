#include "Dragon.h"
#include <iostream>
#include "Player.h"

Dragon::Dragon(int health, int attackPower)
    : BaseMonster("Dragon", health, attackPower) {
    // 드래곤 초기화: 이름, 체력, 공격력 설정
}

// Attack Function Implementation
void Dragon::attack(Player& player) {
    std::cout << "The Goblin attacks you, dealing " << getAttackPower() << " damage!" << std::endl;
    player.takeDamage(getAttackPower());
}