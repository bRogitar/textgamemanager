#include "Ability.h"
#include "Player.h"
#include <iostream>

void Ability::applyEffect(Player& player) const {
    player.modifyHealth(effectValue);
    std::cout << "Applied ability: " << name << " with effect value: " << effectValue << "\n";
}