#include "MonsterFactory.h"
#include "Goblin.h"  // Goblin 헤더 추가
#include "Dragon.h"

std::unique_ptr<BaseMonster> MonsterFactory::createMonster(const std::string& type, int health, int attackPower) {
    if (type == "Goblin") {
        return std::make_unique<Goblin>(health, attackPower);
    } else if (type == "Dragon") {
        return std::make_unique<Dragon>(health, attackPower);
    }
    // 다른 몬스터 타입 추가 가능
    return nullptr; // Unknown type인 경우
}