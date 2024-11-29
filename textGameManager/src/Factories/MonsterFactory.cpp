#include "MonsterFactory.h"

std::unique_ptr<BaseMonster> MonsterFactory::createMonster(
    const std::string& type, const std::string& id, 
    const std::string& name, int health, int attackPower) {
    
    if (type == "Goblin") {
        return std::make_unique<Goblin>(id, name, health, attackPower);
    } 
    else if (type == "Dragon") {
        return std::make_unique<Dragon>(id, name, health, attackPower);
    }

    return nullptr;
} 