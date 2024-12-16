//PosionGasTrap.h

#ifndef POISONGASTRAP_H
#define POISONGASTRAP_H

#include "BaseTrap.h"
#include "Player.h" 
#include <memory>
#include <random>


class PoisonGasTrap : public BaseTrap {
private:
    // 함정 회피 확률 (30%)
    static constexpr int DEFAULT_AVOID_CHANCE = 30;

    /**
     * @brief 플레이어가 함정을 피할 수 있는지 결정
     * @return 회피 성공시 true, 실패시 false
     */
    bool canAvoid() const;

public:
    PoisonGasTrap(const std::string& name, int damage);

    /**
     * @brief 플레이어에 대한 함정 효과 발동
     * @param player 영향을 받을 플레이어
     */
    void trigger(Player& player) override;

    /**
     * @brief 이 함정의 복제본 생성
     * @return std::unique_ptr<BaseTrap> 복제된 함정에 대한 유니크 포인터임
     */
    std::unique_ptr<BaseTrap> clone() const override;
};

#endif // POISONGASTRAP_H