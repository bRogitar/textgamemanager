#ifndef GOBLIN_H
#define GOBLIN_H

#include <iostream>
#include "BaseMonster.h"
#include "Player.h" // Player 클래스가 정의된 헤더 파일을 포함

class Goblin : public BaseMonster {
public:
    Goblin(const std::string& name, int health, int attackPower) : BaseMonster("Goblin", health, attackPower) {}

    // 순수 가상 함수 attack 구현
    void attack(Player& player) override {
        // 고블린의 공격 로직 구현
        std::cout << "Goblin strikes the player with a dagger!" << std::endl;
        player.takeDamage(attackPower);
    }

    // Goblin의 복사본을 생성하는 clone 메서드 구현
    std::unique_ptr<BaseMonster> clone() const override {
        return std::make_unique<Goblin>(*this);
    }
};

#endif // GOBLIN_H
