#ifndef BASEMONSTER_H
#define BASEMONSTER_H

#include <memory>
#include <string>

class Player; // Player 클래스 전방 선언

class BaseMonster {
public:
    virtual ~BaseMonster() = default;

    // 생성자
    BaseMonster(const std::string& name, int health, int attackPower);

    // 순수 가상 함수로 attack 메서드 추가
    virtual void attack(Player& player) = 0;

    // clone 메서드를 순수 가상 함수로 추가
    virtual std::unique_ptr<BaseMonster> clone() const = 0;

    // Getter 메서드
    const std::string& getName() const;
    int getHealth() const;
    int getAttackPower() const;

    // 전투 관련 메서드 추가
    void setHealth(int newHealth);
    bool isCombatDefeated() const;    // 체력이 0 이하인지 여부를 반환
    void takeCombatDamage(int damage); // 데미지를 받고 체력을 감소시킴

    // 새로운 setAttributes 메서드 추가
    void setAttributes(const std::string& name, int health, int attackPower);

    // 상태 출력 메서드 추가
    void displayStatus() const;

protected:
    std::string name; // 이름
    int health;
    int attackPower;
};

#endif // BASEMONSTER_H
