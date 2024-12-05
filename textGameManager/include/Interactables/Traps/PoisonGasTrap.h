#ifndef POISONGASTRAP_H
#define POISONGASTRAP_H

#include "BaseTrap.h"
#include "Player.h"

class PoisonGasTrap : public BaseTrap {
public:
    PoisonGasTrap(const std::string& id, const std::string& name, int damage);
    
    void trigger(Player* player) override;
    bool canAvoid(const Player* player) const override;

private:
    static const int DEFAULT_AVOID_CHANCE = 30; // 기본 회피 확률 30%
};

#endif // POISONGASTRAP_H