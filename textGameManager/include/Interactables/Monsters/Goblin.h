#ifndef GOBLIN_H
#define GOBLIN_H

#include "BaseMonster.h"

class Goblin : public BaseMonster {
public:
    Goblin() : BaseMonster("Goblin", 50, 10) {}
};

#endif // GOBLIN_H
