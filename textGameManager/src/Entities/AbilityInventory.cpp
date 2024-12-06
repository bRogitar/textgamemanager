#include "AbilityInventory.h"
#include <algorithm>
#include <iostream> // Ability 목록을 출력하기 위해 사용

void AbilityInventory::addAbility(std::unique_ptr<Ability> ability) {
    abilities.push_back(std::move(ability));
}

void AbilityInventory::removeAbility(const std::string& abilityId) {
    auto it = std::remove_if(abilities.begin(), abilities.end(),
        [&abilityId](const std::unique_ptr<Ability>& a) { return a->getAbilityId() == abilityId; });
    if (it != abilities.end()) {
        abilities.erase(it, abilities.end());
    }
}

bool AbilityInventory::hasAbility(const std::string& abilityId) const {
    return std::any_of(abilities.begin(), abilities.end(),
        [&abilityId](const std::unique_ptr<Ability>& a) { return a->getAbilityId() == abilityId; });
}

const Ability* AbilityInventory::getAbility(const std::string& abilityId) const {
    auto it = std::find_if(abilities.begin(), abilities.end(),
        [&abilityId](const std::unique_ptr<Ability>& a) { return a->getAbilityId() == abilityId; });
    return it != abilities.end() ? it->get() : nullptr;
}

void AbilityInventory::displayAbilities() const {
    if (abilities.empty()) {
        std::cout << "No abilities available.\n";
        return;
    }

    std::cout << "Available Abilities:\n";
    for (const auto& ability : abilities) {
        std::cout << " - " << ability->getName() << ": " << ability->getDescription() << "\n";
    }
}
