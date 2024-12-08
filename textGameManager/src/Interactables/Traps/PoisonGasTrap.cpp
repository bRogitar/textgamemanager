//PosionGasTrap.cpp

#include "PoisonGasTrap.h"
#include <iostream>
#include <random>

PoisonGasTrap::PoisonGasTrap(const std::string& name, int damage)
    : BaseTrap(name, damage) {}

bool PoisonGasTrap::canAvoid() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    return dis(gen) <= DEFAULT_AVOID_CHANCE;
}

void PoisonGasTrap::trigger(Player& player) {
    if (!canAvoid()) {
        std::cout << getName() << " trap has been triggered! " 
                 << "Taking " << getDamage() << " poison damage." << std::endl;
        player.takeDamage(getDamage());
    } else {
        std::cout << "Successfully avoided the " << getName() << "!" << std::endl;
    }
}

std::unique_ptr<BaseTrap> PoisonGasTrap::clone() const {
    return std::make_unique<PoisonGasTrap>(*this);
}

