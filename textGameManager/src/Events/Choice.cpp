#include "Choice.h"
#include <iostream>

Choice::Choice(const std::string& id, const std::string& description, int healthImpact, int mentalStrengthImpact, int attackPowerImpact, int moneyImpact)
    : id(id), description(description), healthImpact(healthImpact), mentalStrengthImpact(mentalStrengthImpact), attackPowerImpact(attackPowerImpact), moneyImpact(moneyImpact) {}

void Choice::execute(Player& player) const {
    // 플레이어 상태에 영향을 미칩니다.
    player.modifyHealth(healthImpact);
    player.modifyMentalStrength(mentalStrengthImpact);
    player.modifyAttackPower(attackPowerImpact);
    player.modifyMoney(moneyImpact);

    std::cout << "You chose: " << description << std::endl;
}

std::string Choice::getDescription() const {
    return description;
}

std::string Choice::getId() const {
    return id;
}
