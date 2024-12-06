#ifndef HEALTHBOOSTABILITY_H
#define HEALTHBOOSTABILITY_H

#include "Ability.h"
#include "Player.h"

class HealthBoostAbility : public Ability {
public:
    // 기본 생성자 추가
    HealthBoostAbility() : Ability("health_boost", "Health Boost", "Boost your health by 10", 10) {}

    // 기존 생성자
    HealthBoostAbility(const std::string& abilityId, const std::string& name, const std::string& description, int effectValue)
        : Ability(abilityId, name, description, effectValue) {}

    std::unique_ptr<Ability> clone() const override {
        return std::make_unique<HealthBoostAbility>(*this);
    }

    void applyEffect(Player& player) const override {
        player.modifyHealth(getEffectValue());
    }
};

#endif // HEALTHBOOSTABILITY_H
