#ifndef MONSTERFACTORY_H
#define MONSTERFACTORY_H

#include <string>
#include <memory>
#include <unordered_map>
#include "BaseMonster.h"

class MonsterFactory {
public:
    // 몬스터를 생성하는 메서드 
    static std::unique_ptr<BaseMonster> createMonster(const std::string& type, const std::string& name, int health, int attackPower);

    // 몬스터 프로토타입을 등록하는 메서드
    static void registerPrototype(const std::string& type, std::unique_ptr<BaseMonster> prototype);

private:
    // 타입과 프로토타입을 매핑
    static std::unordered_map<std::string, std::unique_ptr<BaseMonster>> prototypes;
};

#endif // MONSTERFACTORY_H
