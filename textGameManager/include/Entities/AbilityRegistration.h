#ifndef ABILITYREGISTRATION_H
#define ABILITYREGISTRATION_H

#include "AbilityFactory.h"

// 매크로를 통해 어빌리티를 자동으로 등록
#define REGISTER_ABILITY(AbilityType, abilityId, abilityName, abilityDesc, effectValue) \
    static bool AbilityType##_registered = []() { \
        AbilityFactory::getInstance().registerAbility(abilityId, std::make_unique<AbilityType>(abilityId, abilityName, abilityDesc, effectValue)); \
        return true; \
    }();


#endif // ABILITYREGISTRATION_H
