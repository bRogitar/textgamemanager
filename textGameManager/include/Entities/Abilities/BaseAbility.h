// Ability.h
#ifndef BASEABILITY_H
#define BASE
ABILITY_H

#include <string>

class Ability {
public:
    Ability(const std::string& abilityId, const std::string& name, const std::string& description, int strengthBoost);
    std::string getAbilityId() const;
    std::string getName() const;
    std::string getDescription() const;
    int getStrengthBoost() const;

private:
    std::string abilityId;
    std::string name;
    std::string description;
    int strengthBoost;

    friend class AbilityInventory;
};

#endif // ABILITY_H
