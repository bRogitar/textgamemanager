#ifndef GETPOTIONACTION_H
#define GETPOTIONACTION_H

#include "BaseAction.h"
#include "Player.h"
#include <iostream>

class GetPotionAction : public BaseAction {
public:
    void execute(Player& player) override {
        //  abilityId를 사용해 능력을 인벤토리에 추가
        std::cout << "You found a Health Boost potion! It has been added to your inventory.\n";
        player.addAbility("health_boost"); // abilityId 사용
    }
};

#endif // GETPOTIONACTION_H
