#ifndef ABILITY_H
#define ABILITY_H

#include <string>

class Ability {
public:
    Ability(const std::string& abilityId, const std::string& name, const std::string& description, int effectValue);
    std::string getAbilityId() const;
    std::string getName() const;
    std::string getDescription() const;
    int getEffectValue() const;

private:
    std::string abilityId;
    std::string name;
    std::string description;
    int effectValue;

    friend class AbilityInventory;
};

#endif // ABILITY_H
