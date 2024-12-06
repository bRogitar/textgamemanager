// Ability.h
#ifndef ABILITY_H
#define ABILITY_H

#include <string>
#include <memory>

class Player;  // Player 클래스 전방 선언

class Ability {
public:
    Ability(const std::string& abilityId, const std::string& name, const std::string& description, int effectValue)
        : abilityId(abilityId), name(name), description(description), effectValue(effectValue) {}

    virtual ~Ability() = default;

    std::string getAbilityId() const { return abilityId; }
    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
    int getEffectValue() const { return effectValue; }

    virtual void applyEffect(Player& player) const = 0; // Player 클래스의 멤버를 사용
    virtual std::unique_ptr<Ability> clone() const = 0;

private:
    std::string abilityId;
    std::string name;
    std::string description;
    int effectValue;
};

#endif // ABILITY_H
