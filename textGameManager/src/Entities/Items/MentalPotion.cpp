#include "MentalPotion.h"
#include "Player.h"

MentalPotion::MentalPotion() : Item(
    "mental_potion", 
    "정신력 물약", 
    "정신력을 30 회복시킵니다.", 
    true) {
    addEffect("mental", 30);
}

void MentalPotion::use(Player& player) const {
    player.modifyMentalStrength(30);
    std::cout << "정신력 물약을 사용했습니다. 정신력이 30 회복되었습니다.\n";
} 