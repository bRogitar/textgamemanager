//NPCTrapRegistration.h

#ifndef NPC_TRAP_REGISTRATION_H
#define NPC_TRAP_REGISTRATION_H

#include "NPCFactory.h"
#include "TrapFactory.h"

#define REGISTER_NPC(TYPE) \
    namespace { \
        struct TYPE##Registration { \
            TYPE##Registration() { \
                auto prototype = std::make_unique<TYPE>("Prototype " #TYPE, "Default Dialog"); \
                NPCFactory::registerPrototype(#TYPE, std::move(prototype)); \
            } \
        }; \
        static TYPE##Registration global_##TYPE##Registration; \
    }

#define REGISTER_TRAP(TYPE) \
    namespace { \
        struct TYPE##Registration { \
            TYPE##Registration() { \
                auto prototype = std::make_unique<TYPE>("Prototype " #TYPE, 10); \
                TrapFactory::registerPrototype(#TYPE, std::move(prototype)); \
            } \
        }; \
        static TYPE##Registration global_##TYPE##Registration; \
    }

#endif