#ifndef COMBATMANAGER_H
#define COMBATMANAGER_H

#include "Player.h"
#include "BaseMonster.h"

class CombatManager {
public:
    CombatManager(Player& player, BaseMonster* monster);

    void startCombat();

private:
    Player& player;
    BaseMonster* monster;

    void combatLoop();
    void playerAttack();
    void monsterAttack();
    void displayCombatStatus() const;
};

#endif // COMBATMANAGER_H