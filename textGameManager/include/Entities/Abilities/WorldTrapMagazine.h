#ifndef WORLDTRAPMAGAZINE_H
#define WORLDTRAPMAGAZINE_H

#include "BaseAbility.h"

class WorldTrapMagazine : public Ability {
public:
    WorldTrapMagazine() : Ability( //일부 선택지에 함정 관련 옵션 추가
        "trap_expertise", 
        "함정 감지", 
        "함정을 회피할 수 있는 추가 선택지가 제공됩니다.", 
        0) {}
};

#endif // WORLDTRAPMAGAZINE_H 