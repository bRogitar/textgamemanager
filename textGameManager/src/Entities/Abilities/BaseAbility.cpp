// Ability.cpp
#include "Ability.h"

Ability::Ability(const std::string& abilityId, const std::string& name, const std::string& description, int strengthBoost)
    : abilityId(abilityId), name(name), description(description), strengthBoost(strengthBoost) {}

std::string Ability::getAbilityId() const {
    return abilityId;
}

std::string Ability::getName() const {
    return name;
}

std::string Ability::getDescription() const {
    return description;
}

int Ability::getStrengthBoost() const {
    return strengthBoost;
}