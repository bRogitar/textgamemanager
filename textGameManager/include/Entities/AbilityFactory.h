#ifndef ABILITYFACTORY_H
#define ABILITYFACTORY_H

#include <memory>
#include "Ability.h"

class AbilityFactory {
public:
    static std::unique_ptr<Ability> createAbility(const std::string& type);
};

#endif // ABILITYFACTORY_H
