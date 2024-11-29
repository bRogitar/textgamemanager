#include "AbilityFactory.h"

std::unique_ptr<Ability> AbilityFactory::createAbility(const std::string& type) {
    if (type == "StrengthBoost") {
        return std::make_unique<Ability>("strength_boost", "Strength Boost", "Increases strength by 10.", 10);
    } else if (type == "HealthBoost") {
        return std::make_unique<Ability>("health_boost", "Health Boost", "Increases health by 20.", 0);
    }
    return nullptr;
} 