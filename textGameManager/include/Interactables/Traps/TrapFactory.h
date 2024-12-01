#ifndef TRAPFACTORY_H
#define TRAPFACTORY_H

#include <memory>
#include "BaseTrap.h"
#include "Pitfall.h"
#include "PoisonGasTrap.h"

class TrapFactory {
public:
    static std::unique_ptr<BaseTrap> createTrap(const std::string& type, const std::string& id, const std::string& name, int damage);
};

#endif // TRAPFACTORY_H
