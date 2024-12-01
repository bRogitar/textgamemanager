#ifndef BASETRAP_H
#define BASETRAP_H

#include <string>
#include "Player.h"

// BaseTrap 클래스: 함정의 기본 기능을 정의하는 추상 클래스
class BaseTrap {
public:
    BaseTrap(const std::string& id, const std::string& name, int damage);

    virtual void trigger(Player* player) = 0;           // 함정을 발동시키는 가상 함수 (상속 클래스에서 구현 필요)
    virtual bool canAvoid(const Player* player) const;  // 함정을 피할 수 있는지 확인하는 가상 함수

    std::string getId() const;
    std::string getName() const;
    int getDamage() const;
    bool isTriggered() const;
    bool isVisible() const;
    void setVisible(bool visible);
    void reset();

protected:
    std::string id;
    std::string name;
    int damage;
    bool triggered;
    bool visible;
};

#endif // BASETRAP_H
