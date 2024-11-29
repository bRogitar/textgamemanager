#include "HealthPotion.h"
#include "Player.h"

HealthPotion::HealthPotion() : Item(
    "health_potion", 
    "체력 물약", 
    "체력을 50 회복시킵니다.", 
    true) {
    addEffect("health", 50);
}

void HealthPotion::use(Player& player) const {
    player.modifyHealth(50);
    std::cout << "체력 물약을 사용했습니다. 체력이 50 회복되었습니다.\n";
} 