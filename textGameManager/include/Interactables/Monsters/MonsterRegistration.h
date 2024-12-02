#ifndef MONSTER_REGISTRATION_H
#define MONSTER_REGISTRATION_H

#include "MonsterFactory.h"

// 몬스터를 팩토리에 자동 등록하는 매크로
#define REGISTER_MONSTER(TYPE) \
    namespace { \
        struct TYPE##Registration { \
            TYPE##Registration() { \
                MonsterFactory::registerMonster(#TYPE, [](int health, int attackPower) { \
                    return std::make_unique<TYPE>(health, attackPower); \
                }); \
            } \
        }; \
        static TYPE##Registration global_##TYPE##Registration; \
    }

#endif // MONSTER_REGISTRATION_H
