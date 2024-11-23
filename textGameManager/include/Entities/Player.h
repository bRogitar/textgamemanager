#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "ItemInventory.h"
#include "AbilityInventory.h"

class Player {
public:
    Player(const std::string& name = "Player", int health = 100, int mentalStrength = 50, int attackPower = 20, int money = 100);

    // Getter and Setter methods
    void setName(const std::string& name);
    std::string getName() const;

    void setHealth(int health);
    int getHealth() const;

    void setMentalStrength(int mentalStrength);
    int getMentalStrength() const;

    void setAttackPower(int attackPower);
    int getAttackPower() const;

    void setMoney(int money);
    int getMoney() const;

    // Modify methods to change status values
    void modifyHealth(int amount);
    void modifyMentalStrength(int amount);
    void modifyAttackPower(int amount);
    void modifyMoney(int amount);

    // Inventory methods
    void addItem(const Item& item);
    void removeItem(const Item& item);
    bool hasItem(const std::string& itemId) const;

    // Ability methods
    void addAbility(const Ability& ability);
    void removeAbility(const Ability& ability);
    bool hasAbility(const std::string& abilityId) const;
    bool isDefeated() const; // 추가된 멤버 함수
    void takeDamage(int damage); // 추가된 멤버 함수
    void applyDefeatPenalty(); // 추가된 멤버 함수

    void setCombatHealth(int health); // 전투 체력 설정 함수
    int getCombatHealth() const; // 전투 체력 가져오기 함수
    void modifyCombatHealth(int amount); // 전투 체력 수정 함수
    bool isCombatDefeated() const; // 전투 체력 기준 패배 여부 확인
    void takeCombatDamage(int damage);
private:
    std::string name;
    int health;
    int mentalStrength;
    int attackPower;
    int combatHealth; // 전투 체력 추가
    int money;

    ItemInventory itemInventory;
    AbilityInventory abilityInventory;
};

#endif // PLAYER_H
