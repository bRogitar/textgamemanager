#include "FightAction.h"

// 생성자 정의
FightAction::FightAction(BaseMonster* monster)
    : monster(monster) {}

// execute 메서드 정의
void FightAction::execute(Player& player) {

    if (monster != nullptr) {
        // 몬스터와 전투를 시작하는 로직 추가
        CombatManager combatManager(player, monster);
        combatManager.startCombat();
    } else {

    }
}
