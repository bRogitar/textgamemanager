#ifndef POISONGASTRAP_H
#define POISONGASTRAP_H

#include "BaseTrap.h"
#include <random>

class PoisonGasTrap : public BaseTrap {
public:
    PoisonGasTrap(int damage, int avoidChance) 
        : BaseTrap(damage), avoidChance(avoidChance) {}

    bool canAvoid(const Player* player) override {
        if (player->hasAbility("trap_codex")) {
            return true;
        }
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);
        return dis(gen) <= avoidChance;
    }

private:
    int avoidChance;
};
