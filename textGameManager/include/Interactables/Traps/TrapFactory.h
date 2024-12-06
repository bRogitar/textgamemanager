//TrapFactory.h

#ifndef TRAPFACTORY_H
#define TRAPFACTORY_H

#include <string>
#include <memory>
#include <unordered_map>
#include "BaseTrap.h"

class TrapFactory {
public:
    static std::unique_ptr<BaseTrap> createTrap(const std::string& type, 
        const std::string& name, int damage);
    static void registerPrototype(const std::string& type, 
        std::unique_ptr<BaseTrap> prototype);

private:
    static std::unordered_map<std::string, std::unique_ptr<BaseTrap>> prototypes;
};

#endif