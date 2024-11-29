// AbilityInventory.h
#ifndef ABILITYINVENTORY_H
#define ABILITYINVENTORY_H

#include <vector>
#include <string>
#include "BaseAbility.h"

class AbilityInventory {
public:
    void addAbility(const BaseAbility& ability);
    void removeAbility(const BaseAbility& ability);
    bool hasAbility(const std::string& abilityId) const;

private:
    std::vector<BaseAbility> abilities;
};

#endif // ABILITYINVENTORY_H


