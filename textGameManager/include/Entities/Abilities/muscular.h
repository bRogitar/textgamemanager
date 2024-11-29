#ifndef MUSCULAR_H
#define MUSCULAR_H

#include "BaseAbility.h"

class Muscular : public BaseAbility {
public:
    Muscular() : BaseAbility(
        "muscular", 
        "근력", 
        "힘으로 안되는 일이 있다면 힘이 부족한 것은 아닌지.", 
        15) {}
};

#endif // MUSCULAR_H 