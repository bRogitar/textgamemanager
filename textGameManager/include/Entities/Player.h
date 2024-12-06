#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "Ability.h"
#include "AbilityInventory.h"
#include <iostream> // 콘솔 출력을 위해 포함

class Player {
public:
    // Constructor
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

    // Combat-related methods
    void setCombatHealth(int health); // 전투 체력 설정 함수
    int getCombatHealth() const; // 전투 체력 가져오기 함수
    void modifyCombatHealth(int amount); // 전투 체력 수정 함수
    bool isCombatDefeated() const; // 전투 체력 기준 패배 여부 확인
    void takeCombatDamage(int damage); // 전투에서 데미지 받기 함수

    // 일반 전투 외 상태 관련 메서드
    bool isDefeated() const; // 게임 오버 여부 확인
    void takeDamage(int damage); // 데미지를 받아 체력 감소
    void applyDefeatPenalty(); // 패배 시 패널티 적용 함수

    // Ability methods
    void addAbility(const std::string& abilityId);  // 어빌리티 추가
    void removeAbility(const std::string& abilityId); // 어빌리티 제거
    bool hasAbility(const std::string& abilityId) const; // 특정 어빌리티 보유 여부 확인
    const Ability* getAbility(const std::string& abilityId) const; // 특정 어빌리티 가져오기
    void useAbility(const std::string& abilityId); // 어빌리티 사용
    void displayAbilities() const; // 보유 중인 어빌리티 표시

    // **Player 상태를 출력하는 메서드 추가**
    void displayStatus() const;

private:
    std::string name;
    int health;
    int mentalStrength;
    int attackPower;
    int money;
    int combatHealth; // 전투 체력

    AbilityInventory abilityInventory; // 어빌리티 인벤토리
};

#endif // PLAYER_H
