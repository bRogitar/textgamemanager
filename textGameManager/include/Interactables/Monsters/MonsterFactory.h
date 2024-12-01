#ifndef MONSTERFACTORY_H
#define MONSTERFACTORY_H

#include <string>
#include <memory>
#include <unordered_map>
#include <functional>
#include "BaseMonster.h"

class MonsterFactory {
public:
    // 몬스터를 생성하는 정적 메서드
    static std::unique_ptr<BaseMonster> createMonster(const std::string& type, int health, int attackPower);

    // 몬스터를 등록하는 정적 메서드
    static void registerMonster(const std::string& type, std::function<std::unique_ptr<BaseMonster>(int, int)> constructor);

private:
    // 타입과 생성자 함수 맵핑
    static std::unordered_map<std::string, std::function<std::unique_ptr<BaseMonster>(int, int)>> registry;
};

#endif // MONSTERFACTORY_H
