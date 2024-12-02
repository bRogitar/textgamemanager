// RunAwayAction.h
#ifndef RUNAWAYACTION_H
#define RUNAWAYACTION_H

#include "BaseAction.h"
#include <iostream>

class RunAwayAction : public BaseAction {
public:
    void execute(Player& player) override {
        std::cout << "You decided to run away from the fight!" << std::endl;
        // 도망가는 경우, 예를 들어 체력을 줄이거나 다른 효과 적용
        player.setMentalStrength(player.getMentalStrength() - 10);
    }
};

#endif // RUNAWAYACTION_H