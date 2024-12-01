#include "TrapFactory.h"

std::unique_ptr<BaseTrap> TrapFactory::createTrap(const std::string& type, const std::string& id, const std::string& name, int damage) {
    if (type == "Pitfall") {
        return std::make_unique<Pitfall>(id, name, damage);
    } else if (type == "PoisonGasTrap") {
        return std::make_unique<PoisonGasTrap>(id, name, damage);
    }
    return nullptr;
}
