#ifndef MONSTERFACTORY_H
#define MONSTERFACTORY_H

#include <memory>
#include "BaseMonster.h"
#include "Goblin.h"
#include "Dragon.h"

class MonsterFactory {
public:
    static std::unique_ptr<BaseMonster> createMonster(const std::string& type,
        const std::string& id, const std::string& name, int health, int attackPower);
};

#endif // MONSTERFACTORY_H
