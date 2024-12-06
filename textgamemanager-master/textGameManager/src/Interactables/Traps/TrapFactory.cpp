//TrapFactory.cpp

#include "TrapFactory.h"

std::unordered_map<std::string, std::unique_ptr<BaseTrap>> TrapFactory::prototypes;

std::unique_ptr<BaseTrap> TrapFactory::createTrap(const std::string& type, const std::string& name, int damage) {
    auto it = prototypes.find(type);
    if (it != prototypes.end()) {
        auto trap = it->second->clone();
        trap->setAttributes(name, damage);
        return trap;
    }
    return nullptr;
}

void TrapFactory::registerPrototype(const std::string& type, std::unique_ptr<BaseTrap> prototype) {
    prototypes[type] = std::move(prototype);
}