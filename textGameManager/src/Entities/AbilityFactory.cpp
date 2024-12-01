#include "AbilityFactory.h"
#include "Ability.h"

// 피의정수: 최대체력 20 증가
class BloodEssence : public Ability {
public:
    BloodEssence() : Ability("blood_essence", "피의정수", "최대 체력 20 증가", 20) {}
};

// 근력: 이벤트 추가 선택지용
class Strength : public Ability {
public:
    Strength() : Ability("strength", "근력", "특정 이벤트에서 추가 선택지 제공", 0) {}
};

// 세계함정도감: 함정 해체에 사용
class WorldTrapCodex : public Ability {
public:
    WorldTrapCodex() : Ability("trap_codex", "세계함정도감", "함정을 해체하고 통과 가능", 0) {}
};

// 무식하게 큰 대검: 기본 공격력 20 증가
class MassiveGreatsword : public Ability {
public:
    MassiveGreatsword() : Ability("greatsword", "무식하게 큰 대검", "기본 공격력 20 증가", 20) {}
};

std::unique_ptr<Ability> AbilityFactory::createAbility(const std::string& type) {
    if (type == "blood_essence") {
        return std::make_unique<BloodEssence>();
    } else if (type == "strength") {
        return std::make_unique<Strength>();
    } else if (type == "trap_codex") {
        return std::make_unique<WorldTrapCodex>();
    } else if (type == "greatsword") {
        return std::make_unique<MassiveGreatsword>();
    }
    return nullptr;
}
