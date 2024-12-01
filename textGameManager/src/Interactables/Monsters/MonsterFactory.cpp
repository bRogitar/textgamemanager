#include "MonsterFactory.h"

// 정적 멤버 초기화
std::unordered_map<std::string, std::function<std::unique_ptr<BaseMonster>(int, int)>> MonsterFactory::registry;

std::unique_ptr<BaseMonster> MonsterFactory::createMonster(const std::string& type, int health, int attackPower) {
    auto it = registry.find(type);
    if (it != registry.end()) {
        // 등록된 생성자를 사용하여 몬스터 생성
        return it->second(health, attackPower);
    }
    return nullptr; // 등록되지 않은 타입
}

void MonsterFactory::registerMonster(const std::string& type, std::function<std::unique_ptr<BaseMonster>(int, int)> constructor) {
    registry[type] = constructor;
}
