#include "MonsterFactory.h"

// 초기화
std::unordered_map<std::string, std::unique_ptr<BaseMonster>> MonsterFactory::prototypes;

// 몬스터를 생성하는 메서드
std::unique_ptr<BaseMonster> MonsterFactory::createMonster(const std::string& type, const std::string& name, int health, int attackPower) {
    auto it = prototypes.find(type);
    if (it != prototypes.end()) {
        auto monster = it->second->clone();  // 프로토타입을 복사
        monster->setAttributes(name, health, attackPower); // XML에서 읽은 값을 설정
        return monster;
    }
    return nullptr;
}

// 몬스터 프로토타입을 등록하는 메서드
void MonsterFactory::registerPrototype(const std::string& type, std::unique_ptr<BaseMonster> prototype) {
    prototypes[type] = std::move(prototype);
}
