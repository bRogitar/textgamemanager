// AbilityInventory.h
#ifndef ABILITYINVENTORY_H
#define ABILITYINVENTORY_H

#include <vector>
#include <string>
#include "BaseAbility.h"

class AbilityInventory {
public:
    void addAbility(const Ability& ability);
    void removeAbility(const Ability& ability);
    bool hasAbility(const std::string& abilityId) const;

private:
    std::vector<Ability> abilities;
};

#endif // ABILITYINVENTORY_H


