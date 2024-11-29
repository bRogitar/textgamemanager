#ifndef GOBLIN_H
#define GOBLIN_H

#include "BaseMonster.h"
#include "Player.h"

class Goblin : public BaseMonster {
public:
    Goblin(int health, int attackPower);
    void attack(Player& player) override;
};

#endif // GOBLIN_H