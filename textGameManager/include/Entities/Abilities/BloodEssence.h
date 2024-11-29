#ifndef BLOODESSENCE_H
#define BLOODESSENCE_H

#include "BaseAbility.h"

class BloodEssence : public Ability {
public:
    BloodEssence() : Ability(
        "blood_essence", 
        "피의 정수", 
        "최대 체력을 20 증가시킵니다.", 
        true) {
        addEffect("max_health", 20);
    }
};

#endif // BLOODESSENCE_H 