#ifndef DRAGON_H
#define DRAGON_H

#include "BaseMonster.h"
#include <iostream>
#include <string>
#include "Player.h"

class Dragon : public BaseMonster {
public:
    // 생성자를 수정하여 이름, 체력, 공격력을 모두 받을 수 있도록 변경
    Dragon(const std::string& name, int health, int attackPower)
        : BaseMonster(name, health, attackPower) {}

    // 공격 메서드 정의
    void attack(Player& player) override {
        std::cout << name << " breathes fire at the player!" << std::endl;
        player.takeDamage(attackPower);
    }

    // 복제 메서드 정의
    std::unique_ptr<BaseMonster> clone() const override {
        return std::make_unique<Dragon>(*this);
    }
};

#endif // DRAGON_H
