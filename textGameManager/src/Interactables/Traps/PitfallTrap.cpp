#include "PitfallTrap.h"

PitfallTrap::PitfallTrap(const std::string& name, int damage)
    : BaseTrap(name, damage) {}

bool PitfallTrap::canAvoid() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    return dis(gen) <= DEFAULT_AVOID_CHANCE;
}

void PitfallTrap::trigger(Player& player) {
    if (!canAvoid()) {
        std::cout << getName() << "you fall into a pitfall! " 
                 << getDamage() << " fall damage" << std::endl;
        player.takeDamage(getDamage());
    } else {
        std::cout << getName() << " Successfully avoided the" << std::endl;
    }
}

std::unique_ptr<BaseTrap> PitfallTrap::clone() const {
    return std::make_unique<PitfallTrap>(*this);
} 