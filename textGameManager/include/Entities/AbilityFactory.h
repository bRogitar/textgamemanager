#ifndef ABILITYFACTORY_H
#define ABILITYFACTORY_H

#include "Ability.h"
#include <unordered_map>
#include <memory>
#include <string>

class AbilityFactory {
public:
    static AbilityFactory& getInstance();

    // 어빌리티 프로토타입 등록 메서드
    void registerAbility(const std::string& abilityName, std::unique_ptr<Ability> prototype);

    // 어빌리티 생성 메서드 (프로토타입 복제)
    std::unique_ptr<Ability> createAbility(const std::string& abilityName);

private:
    AbilityFactory() = default;

    // 프로토타입을 관리하는 맵 (하나로 통합)
    std::unordered_map<std::string, std::unique_ptr<Ability>> prototypes;
};

#endif // ABILITYFACTORY_H
