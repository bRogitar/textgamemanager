#ifndef BASEMONSTER_H
#define BASEMONSTER_H

#include <string>
#include "Player.h"

class BaseMonster {
public:
    BaseMonster(const std::string& name, int health, int attackPower);

    virtual void attack(Player& player) = 0; // 순수 가상 함수

    std::string getName() const;
    int getHealth() const;
    int getAttackPower() const;

    void setCombatHealth(int newHealth);
    int getCombatHealth() const;
    bool isCombatDefeated() const;
    void takeCombatDamage(int damage);

protected:
    int health;        // Initial health of the monster
    int attackPower;   // Attack power of the monster
    int combatHealth;  // Current health during combat

private:
    std::string name;  // Name of the monster
};

#endif // BASEMONSTER_H
