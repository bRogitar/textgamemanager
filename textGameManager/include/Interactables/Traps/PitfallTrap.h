//PitfallTrap.h

#ifndef PITFALLTRAP_H
#define PITFALLTRAP_H

#include "BaseTrap.h"
#include "Player.h" 
#include <memory>
#include <random>

/**
 * @class PitfallTrap
 * @brief 구덩이에 빠져 플레이어에게 데미지를 주는 트랩
 * @inherit BaseTrap
 */
class PitfallTrap : public BaseTrap {
private:
    // 트랩 회피 확률 (20%)
    static constexpr int DEFAULT_AVOID_CHANCE = 50;

    bool canAvoid() const;

public:
    PitfallTrap(const std::string& name, int damage);
    void trigger(Player& player) override;
    std::unique_ptr<BaseTrap> clone() const override;
};

#endif // PITFALLTRAP_H
