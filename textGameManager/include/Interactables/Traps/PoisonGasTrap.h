#ifndef POISONGASTRAP_H
#define POISONGASTRAP_H

#include "BaseTrap.h"
#include "Player.h" 
#include <memory>
#include <random>

/**
 * @class PoisonGasTrap
 * @brief A trap that releases poisonous gas, dealing damage to the player
 * @inherit BaseTrap
 */
class PoisonGasTrap : public BaseTrap {
private:
    // Chance to avoid the trap (30%)
    static constexpr int DEFAULT_AVOID_CHANCE = 30;

    /**
     * @brief Determines if the player can avoid the trap
     * @return true if avoided, false otherwise
     */
    bool canAvoid() const;

public:
    /**
     * @brief Construct a new Poison Gas Trap
     * @param name The name of the trap
     * @param damage The amount of damage the trap deals
     */
    PoisonGasTrap(const std::string& name, int damage);

    /**
     * @brief Trigger the trap effect on the player
     * @param player The player to affect
     */
    void trigger(Player& player) override;

    /**
     * @brief Create a clone of this trap
     * @return std::unique_ptr<BaseTrap> A unique pointer to the cloned trap
     */
    std::unique_ptr<BaseTrap> clone() const override;
};

#endif // POISONGASTRAP_H