#include "Goblin.h"
#include <iostream>
#include "Player.h"

// Goblin Constructor Definition
Goblin::Goblin(int health, int attackPower)
    : BaseMonster("Goblin", health, attackPower) {}  // BaseMonster의 생성자 호출

// Attack Function Implementation
void Goblin::attack(Player& player) {
    std::cout << "The Goblin attacks you, dealing " << getAttackPower() << " damage!" << std::endl;
    player.takeDamage(getAttackPower());
}