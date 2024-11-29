#ifndef COMBATMANAGER_H
#define COMBATMANAGER_H

#include "Player.h"
#include "BaseMonster.h"

class CombatManager {
public:
    CombatManager(Player& player, BaseMonster* monster);

    // Public method to start the combat
    void startCombat();

private:
    Player& player;
    BaseMonster* monster;

    // Private methods for combat loop, player attack, monster attack, and status display
    void combatLoop();
    void playerAttack();
    void monsterAttack();
    void displayCombatStatus() const;
};

#endif // COMBATMANAGER_H
