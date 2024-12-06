// ClimbWallAction.h
#ifndef CLIMBWALLACTION_H
#define CLIMBWALLACTION_H

#include "BaseAction.h"
#include <iostream>

class ClimbWallAction : public BaseAction {
public:
    void execute(Player& player) override {
        std::cout << "You decided to climb the wall!" << std::endl;
        // 벽을 타기로 했을 때의 효과 (예: 체력 소모 또는 상태 변화 등)
        player.setHealth(player.getHealth() - 5);
    }
};

#endif // CLIMBWALLACTION_H
