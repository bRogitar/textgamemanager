#include "TrapFactory.h"

std::unique_ptr<BaseTrap> TrapFactory::createTrap(
    const std::string& type, const std::string& id,
    const std::string& name, int damage) {
    
    if (type == "PoisonGas") {
        return std::make_unique<PoisonGasTrap>(id, name, damage);
    }
    else if (type == "Spike") {
        return std::make_unique<SpikeTrap>(id, name, damage);
    }
    // else if (type == "FireTrap") {
    //     return std::make_unique<FireTrap>(id, name, damage);
    // }
    return nullptr;
} 