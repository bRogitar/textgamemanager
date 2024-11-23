#ifndef MONSTERFACTORY_H
#define MONSTERFACTORY_H

#include <string>
#include <memory>
#include "BaseMonster.h"
#include "Goblin.h" // 구체적인 몬스터 클래스 포함

class MonsterFactory {
public:
    static std::unique_ptr<BaseMonster> createMonster(const std::string& type, int health, int attackPower);
};

#endif // MONSTERFACTORY_H
