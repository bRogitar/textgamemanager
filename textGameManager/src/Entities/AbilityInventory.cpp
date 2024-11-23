// AbilityInventory.cpp
#include "AbilityInventory.h"
#include <algorithm>

void AbilityInventory::addAbility(const Ability& ability) {
    abilities.push_back(ability);
}

void AbilityInventory::removeAbility(const Ability& ability) {
    auto it = std::remove_if(abilities.begin(), abilities.end(),
        [&ability](const Ability& a) { return a.abilityId == ability.abilityId; });
    if (it != abilities.end()) {
        abilities.erase(it, abilities.end());
    }
}

bool AbilityInventory::hasAbility(const std::string& abilityId) const {
    return std::any_of(abilities.begin(), abilities.end(),
        [&abilityId](const Ability& a) { return a.abilityId == abilityId; });
}