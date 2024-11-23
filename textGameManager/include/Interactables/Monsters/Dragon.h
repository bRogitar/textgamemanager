#ifndef DRAGON_H
#define DRAGON_H

#include "BaseMonster.h"

class Dragon : public BaseMonster {
public:
    Dragon() : BaseMonster("Dragon", 200, 40) {}
};

#endif // DRAGON_H
