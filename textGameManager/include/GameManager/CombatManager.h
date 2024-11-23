#ifndef COMBATMANAGER_H
#define COMBATMANAGER_H

#include "BaseMonster.h"
#include "Player.h"

class CombatManager {
public:
    CombatManager(Player& player, BaseMonster* monster);
    void startCombat();

private:
    Player& player;
    BaseMonster* monster;
    void playerAttack();
    void monsterAttack();
    void displayCombatStatus() const;
    void combatLoop();
};

#endif // COMBATMANAGER_H
