#ifndef BASEMONSTER_H
#define BASEMONSTER_H

#include <string>

class BaseMonster {
public:
    BaseMonster(const std::string& name, int health, int attackPower);
    
    void setCombatHealth(int health);
    int getCombatHealth() const;
    void takeCombatDamage(int damage);
    bool isCombatDefeated() const;

    std::string getName() const;
    int getHealth() const;
    int getAttackPower() const;

private:
    std::string name;
    int health; // Overall health
    int attackPower;
    int combatHealth; // Combat-specific health
};

#endif // BASEMONSTER_H
