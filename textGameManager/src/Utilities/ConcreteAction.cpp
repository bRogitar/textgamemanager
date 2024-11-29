#include "ConcreteAction.h"

// 생성자 정의
ConcreteAction::ConcreteAction(BaseMonster* monster)
    : monster(monster) {}

// execute 메서드 정의
void ConcreteAction::execute(Player& player) {

    if (monster != nullptr) {
        // 몬스터와 전투를 시작하는 로직 추가
        CombatManager combatManager(player, monster);
        combatManager.startCombat();
    } else {

    }
}
