#ifndef MONSTER_REGISTRATION_H
#define MONSTER_REGISTRATION_H

#include "MonsterFactory.h"

// 몬스터를 팩토리에 자동 등록하는 매크로 (프로토타입 등록)
#define REGISTER_MONSTER(TYPE) \
    namespace { \
        struct TYPE##Registration { \
            TYPE##Registration() { \
                auto prototype = std::make_unique<TYPE>("Prototype " #TYPE, 100, 20); \
                MonsterFactory::registerPrototype(#TYPE, std::move(prototype)); \
            } \
        }; \
        static TYPE##Registration global_##TYPE##Registration; \
    }

#endif // MONSTER_REGISTRATION_H
