// PlayerStatus.cpp
#include "PlayerStatus.h"

PlayerStatus::PlayerStatus() : health(100), mentalStrength(50), attackPoint(10) {}

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

void PlayerStatus::modifyAttackPonint(int amount){
    attackPoint += amount;
    if (attackPoint < 0) {
        attackPoint = 0;
    }
}

int PlayerStatus::getHealth() const {
    return health;
}

int PlayerStatus::getMentalStrength() const {
    return mentalStrength;
}

int PlayerStatus::getAttackPonint() const {
    return attackPoint;
}

