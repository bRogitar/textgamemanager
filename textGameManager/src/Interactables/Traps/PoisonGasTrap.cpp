//PosionGasTrap.cpp

#include "PoisonGasTrap.h"
#include <iostream>
#include <random>

bool PoisonGasTrap::canAvoid(const Player* player) const {
    // 함정 도감 능력이 있으면 자동 회피
    if (player->hasAbility("trap_codex")) {
        return true;
    }
    
    // 기본 회피 확률 계산
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    return dis(gen) <= DEFAULT_AVOID_CHANCE;
}

void PoisonGasTrap::trigger(Player* player) {
    if (!isTriggered()) {
        if (!canAvoid(player)) {
            std::cout << getName() << " 함정이 발동되었습니다! " 
                     << getDamage() << "의 독 피해를 입었습니다." << std::endl;
            player->takeDamage(getDamage());
        } else if (player->hasAbility("trap_codex")) {
            std::cout << "세계함정도감을 사용하여 " << getName() 
                     << "을(를) 성공적으로 발견하고 해체했습니다!" << std::endl;
        } else {
            std::cout << getName() << "을(를) 피하는 데 성공했습니다!" << std::endl;
        }
        triggered = true;  // 함정 발동 상태로 설정
    }
}