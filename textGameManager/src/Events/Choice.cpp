// Choice.cpp
#include "Choice.h"

Choice::Choice(const std::string& id, const std::string& description, int healthImpact, int mentalStrengthImpact, int attackPowerImpact, int moneyImpact)
    : id(id), description(description), healthImpact(healthImpact), mentalStrengthImpact(mentalStrengthImpact), attackPowerImpact(attackPowerImpact), moneyImpact(moneyImpact) {}

void Choice::execute(Player& player) const {
    player.modifyHealth(healthImpact);
    player.modifyMentalStrength(mentalStrengthImpact);
    player.modifyAttackPower(attackPowerImpact);
    player.modifyMoney(moneyImpact);
}

std::string Choice::getDescription() const {
    return description;
}