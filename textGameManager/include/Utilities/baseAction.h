// BaseAction.h
#ifndef BASEACTION_H
#define BASEACTION_H

#include "Player.h"

class BaseAction {
public:
    virtual ~BaseAction() = default;
    virtual void execute(Player& player) = 0; // 각 행동에서 구현해야 하는 함수
};

#endif // BASEACTION_H