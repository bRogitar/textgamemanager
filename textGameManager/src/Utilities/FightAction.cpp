#include "FightAction.h"
#include "CombatManager.h"
#include <iostream>

FightAction::FightAction(BaseMonster* monster) : monster(monster) {}

void FightAction::execute(Player& player) {
    if (monster != nullptr) {
        std::cout << "You chose to fight the " << monster->getName() << "!\n";

        // CombatManager를 이용해 전투 시작
        CombatManager combatManager(player, monster);
        combatManager.startCombat();
    } else {
        std::cout << "No monster found to fight.\n";
    }
}
