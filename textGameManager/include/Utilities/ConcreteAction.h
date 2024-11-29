#ifndef CONCRETEACTION_H
#define CONCRETEACTION_H

#include "BaseAction.h"
#include "Player.h"
#include "BaseMonster.h"
#include "CombatManager.h"
#include <iostream>

class ConcreteAction : public BaseAction {
private:
    BaseMonster* monster; // 전투 대상 몬스터

public:
    ConcreteAction(BaseMonster* monster = nullptr); // 생성자 선언

    void execute(Player& player) override; // execute 메서드 선언
};

#endif // CONCRETEACTION_H
