#ifndef GOBLIN_H
#define GOBLIN_H
#include <iostream>
#include "BaseMonster.h"

class Goblin : public BaseMonster {
public:
    Goblin(int health, int attackPower)
        : BaseMonster("Goblin", health, attackPower) {}

    // 순수 가상 함수 attack 구현
    void attack(Player& player) override {
        // 고블린의 공격 로직 구현
        std::cout << "Goblin strikes the player with a dagger!" << std::endl;
        player.takeDamage(attackPower);
    }
};

#endif // GOBLIN_H
