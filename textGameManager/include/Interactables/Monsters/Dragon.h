#ifndef DRAGON_H
#define DRAGON_H
#include <iostream>
#include "BaseMonster.h"

class Dragon : public BaseMonster {
public:
    Dragon(int health, int attackPower)
        : BaseMonster("Dragon", health, attackPower) {}

    void attack(Player& player) override {
        std::cout << "Dragon breathes fire on the player, causing " << getAttackPower() << " damage!" << std::endl;
        player.takeDamage(getAttackPower());
    }
};

#endif // DRAGON_H
