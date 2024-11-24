#ifndef BASETRAP_H
#define BASETRAP_H

#include <string>
#include "../../Entities/Player.h"

// BaseTrap 클래스: 함정의 기본 기능을 정의하는 추상 클래스
class BaseTrap {
public:
    // 생성자: 함정의 ID, 이름, 데미지를 설정합니다.
    BaseTrap(const std::string& id, const std::string& name, int damage);

    // Getter 메서드들
    std::string getId() const;         // 함정의 ID를 반환
    std::string getName() const;       // 함정의 이름을 반환
    int getDamage() const;             // 함정의 데미지를 반환
    bool isTriggered() const;          // 함정이 발동되었는지 여부를 반환
    bool isVisible() const;            // 함정이 보이는지 여부를 반환

    // 함정 기능
    virtual void trigger(Player* player) = 0;           // 함정을 발동시키는 가상 함수 (상속 클래스에서 구현 필요)
    virtual bool canAvoid(const Player* player) const;  // 함정을 피할 수 있는지 확인하는 가상 함수
    void setVisible(bool visible);                      // 함정의 가시성 설정
    void reset();                                       // 함정을 초기 상태로 되도라ㅣㅁ

protected:
    std::string id;         // 고유 ID
    std::string name;       // 이름
    int damage;             // 데미지
    bool triggered;         // 발동되었는지 여부
    bool visible;           // 보이는지 여부
};

#endif // BASETRAP_H
