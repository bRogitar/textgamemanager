// PlayerStatus.cpp
#include "PlayerStatus.h"

PlayerStatus::PlayerStatus() : health(100), mentalStrength(50) {}

void PlayerStatus::modifyHealth(int amount) {
    health += amount;
    if (health < 0) {
        health = 0;
    }
}

void PlayerStatus::modifyMentalStrength(int amount) {
    mentalStrength += amount;
    if (mentalStrength < 0) {
        mentalStrength = 0;
    }
}

int PlayerStatus::getHealth() const {
    return health;
}

int PlayerStatus::getMentalStrength() const {
    return mentalStrength;
}