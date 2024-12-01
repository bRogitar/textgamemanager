#include "Ability.h"

Ability::Ability(const std::string& abilityId, const std::string& name, const std::string& description, int effectValue)
    : abilityId(abilityId), name(name), description(description), effectValue(effectValue) {}

std::string Ability::getAbilityId() const {
    return abilityId;
}

std::string Ability::getName() const {
    return name;
}

std::string Ability::getDescription() const {
    return description;
}

int Ability::getEffectValue() const {
    return effectValue;
}
