#ifndef CHOICE_H
#define CHOICE_H

#include <string>
#include "Player.h"

class Choice {
public:
    Choice(const std::string& id, const std::string& description, int healthImpact = 0, int mentalStrengthImpact = 0, int attackPowerImpact = 0, int moneyImpact = 0);
    
    void execute(Player& player) const;
    std::string getDescription() const;
    std::string getId() const;  // 선택지 ID 반환

private:
    std::string id;  // 선택지의 고유 ID
    std::string description;
    int healthImpact;
    int mentalStrengthImpact;
    int attackPowerImpact;
    int moneyImpact;
};

#endif // CHOICE_H
