#ifndef MUSCULAR_H
#define MUSCULAR_H

#include "BaseAbility.h"

class muscular : public Ability {
public:
    muscular() : Ability(   //힘 관련된 선택지 용 능력
        "muscular", 
        "근력", 
        "힘으로 안되는 일이 있다면 힘이 부족한 것은 아닌지.", 
        15) {}
};

#endif // MUSCULAR_H 