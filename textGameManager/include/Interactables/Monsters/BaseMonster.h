#ifndef BASEMONSTER_H
#define BASEMONSTER_H

#include <string>
#include "Player.h"

class BaseMonster {
public:
    BaseMonster(const std::string& name, int health, int attackPower);

    virtual void attack(Player& player) = 0; 

    std::string getName() const;
    int getHealth() const;
    int getAttackPower() const;

    void setCombatHealth(int newHealth);
    int getCombatHealth() const;
    bool isCombatDefeated() const;
    void takeCombatDamage(int damage);

protected:
    int health;        
    int attackPower;   
    int combatHealth; 

private:
    std::string name;  
};

#endif // BASEMONSTER_H
