#ifndef POISONGASTRAP_H
#define POISONGASTRAP_H

#include "BaseTrap.h"
#include "Player.h"

class PoisonGasTrap : public BaseTrap {
public:
    PoisonGasTrap(const std::string& name, int damage);
    
    void trigger(Player& player) override;
    std::unique_ptr<BaseTrap> clone() const override;
    bool canAvoid() const;

private:
    static const int DEFAULT_AVOID_CHANCE = 30;
};