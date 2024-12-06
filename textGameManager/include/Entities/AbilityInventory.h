#ifndef ABILITYINVENTORY_H
#define ABILITYINVENTORY_H

#include "Ability.h" // Ability 클래스를 사용하기 위해 Ability 헤더 파일을 포함
#include <vector>
#include <memory>
#include <string>

class AbilityInventory {
public:
    // 어빌리티 추가 및 제거 메서드
    void addAbility(std::unique_ptr<Ability> ability);
    void removeAbility(const std::string& abilityId);
    bool hasAbility(const std::string& abilityId) const;
    const Ability* getAbility(const std::string& abilityId) const;
    
    // 어빌리티 목록을 출력하는 메서드
    void displayAbilities() const;
    const std::vector<std::unique_ptr<Ability>>& getAbilities() const {
        return abilities;
    }

    bool isEmpty() const {
        return abilities.empty();
    }
private:
    std::vector<std::unique_ptr<Ability>> abilities; // 어빌리티들을 저장하는 벡터
};

#endif // ABILITYINVENTORY_H
