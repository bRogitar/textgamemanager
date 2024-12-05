//PosionGasTrap.cpp

#include "PoisonGasTrap.h"
#include <iostream>
#include <random>

PoisonGasTrap::PoisonGasTrap(const std::string& name, int damage)
    : BaseTrap(name, damage) {}

void PoisonGasTrap::trigger(Player& player) {
    if (!canAvoid()) {
        std::cout << getName() << " 함정이 발동되었습니다! " 
                 << getDamage() << "의 독 피해를 입었습니다." << std::endl;
        player.takeDamage(getDamage());
    } else {
        std::cout << getName() << "을(를) 피하는 데 성공했습니다!" << std::endl;
    }
}

std::unique_ptr<BaseTrap> PoisonGasTrap::clone() const {
    return std::make_unique<PoisonGasTrap>(*this);
}

bool PoisonGasTrap::canAvoid() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    return dis(gen) <= DEFAULT_AVOID_CHANCE;
}