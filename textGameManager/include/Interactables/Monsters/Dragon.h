#ifndef DRAGON_H
#define DRAGON_H

#include "BaseMonster.h"

class Dragon : public BaseMonster {
public:
    Dragon(int health = 200, int attackPower = 40);
};

#endif // DRAGON_H
