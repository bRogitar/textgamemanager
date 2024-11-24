#ifndef BASEMONSTER_H
#define BASEMONSTER_H

#include <string>
#include "Player.h"

class BaseMonster {
public:
    BaseMonster(const std::string& name, int health, int attackPower);

    virtual ~BaseMonster() = default;

    // Getter methods
    std::string getName() const;
    int getHealth() const;
    int getCombatHealth() const;
    int getAttackPower() const;

    // Combat related methods
    void setCombatHealth(int health);
    void takeCombatDamage(int damage);
    bool isCombatDefeated() const;

    // Virtual attack method to be overridden by derived classes
    virtual void attack(Player& player) = 0;

private:
    std::string name;
    int health;
    int combatHealth; // Combat health to track during battles
    int attackPower;
};

#endif // BASEMONSTER_H
