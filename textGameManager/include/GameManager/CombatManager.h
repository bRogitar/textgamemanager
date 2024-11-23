// CombatManager.h
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
    BaseMonster* monster; // Use pointer type to match the constructor in Event class
    void playerAttack();
    void monsterAttack();
    void displayCombatStatus() const;
    void combatLoop();
};

#endif // COMBATMANAGER_H
