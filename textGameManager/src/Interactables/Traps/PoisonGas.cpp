#include "PoisonGas.h"
#include "Player.h"
#include <random>

PoisonGasTrap::PoisonGasTrap(int damage, int avoidChance) 
    : BaseTrap(damage), avoidChance(avoidChance) {}

bool PoisonGasTrap::canAvoid(const Player* player) {
    if (player->hasAbility("trap_codex")) {
        return true;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    return dis(gen) <= avoidChance;
}

void PoisonGasTrap::trigger(Player* player) {
    if (!canAvoid(player)) {
        std::cout << "독가스 함정이 발동되었습니다! " << getDamage() << "의 피해를 입었습니다." << std::endl;
        player->takeDamage(getDamage());
        } else if (player->hasAbility("trap_codex")) {
            std::cout << "세계함정도감을 사용하여 독가스 함정을 성공적으로 발견하고 해체했습니다!" << std::endl;
        } else {
            std::cout << "당신은 독가스 함정을 피하는 데 성공했습니다!" << std::endl;

    }
}