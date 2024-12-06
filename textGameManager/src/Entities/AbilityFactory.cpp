#include "AbilityFactory.h"

// AbilityFactory 싱글턴 인스턴스 반환
AbilityFactory& AbilityFactory::getInstance() {
    static AbilityFactory instance;
    return instance;
}

// Ability 프로토타입 등록 메서드
void AbilityFactory::registerAbility(const std::string& abilityName, std::unique_ptr<Ability> prototype) {
    prototypes[abilityName] = std::move(prototype);
}

// Ability를 팩토리에서 생성하는 메서드 (복제)
std::unique_ptr<Ability> AbilityFactory::createAbility(const std::string& abilityName) {
    auto it = prototypes.find(abilityName);
    if (it != prototypes.end()) {
        return it->second->clone();
    }
    return nullptr;
}
