#ifndef POISONGASTRAP_H
#define POISONGASTRAP_H

#include "BaseTrap.h"

// PoisonGasTrap 클래스: 함정의 일종인 독가스 함정을 정의하는 클래스
class PoisonGasTrap : public BaseTrap {
public:
    // 생성자: 독가스 함정의 ID, 이름, 데미지, 지속 시간, 턴당 데미지를 설정합니다.
    PoisonGasTrap(const std::string& id, const std::string& name, int damage,
                  int poisonDuration, int poisonDamagePerTurn);

    // 함정 기능 재정의
    void trigger(Player* player) override;             // 플레이어에게 함정을 발동시킵니다.
    bool canAvoid(const Player* player) const override; // 플레이어가 독가스를 피할 수 있는지 확인합니다.

    // 독가스 관련 메서드들
    int getPoisonDuration() const;                      // 독가스 지속 시간을 반환합니다.
    int getPoisonDamagePerTurn() const;                 // 턴당 독가스 데미지를 반환합니다.

private:
    int poisonDuration;         // 독가스 지속 시간
    int poisonDamagePerTurn;    // 턴당 독가스 데미지
};

#endif // POISONGASTRAP_H
