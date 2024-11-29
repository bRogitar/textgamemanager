#ifndef DRAGON_H
#define DRAGON_H

#include "BaseMonster.h"
#include <iostream>

class Dragon : public BaseMonster {
public:
    Dragon(int health, int attackPower);
    void attack(Player& player) override;
};

#endif // DRAGON_H