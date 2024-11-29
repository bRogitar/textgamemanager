// RunAwayAction.h
#ifndef RUNAWAYACTION_H
#define RUNAWAYACTION_H

#include "BaseAction.h"
#include <iostream>

class RunAwayAction : public BaseAction {
public:
    void execute(Player& player) override {
        std::cout << "You decided to run away from the trap!" << std::endl;
        // 도망가기로 했을 때의 효과 (예: 체력 손실 또는 위치 이동 등)
        player.setMentalStrength(player.getMentalStrength() - 10);
    }
};

#endif // RUNAWAYACTION_H
