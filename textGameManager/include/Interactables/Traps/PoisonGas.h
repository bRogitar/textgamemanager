#ifndef PITFALL_H
#define PITFALL_H

#include "BaseTrap.h"

// Pitfall 클래스: 함정의 일종인 구덩이 함정을 정의하는 클래스
class Pitfall : public BaseTrap {
public:
    // 생성자: 구덩이 함정의 ID, 이름, 데미지, 깊이를 설정
    Pitfall(const std::string& id, const std::string& name, int damage, int depth);

    // 함정 기능 재정의
    void trigger(Player* player) override;  // 플레이어에게 함정을 발동시

    // Pitfall-specific 메서드
    int getDepth() const;                   // 구덩이의 깊이를 반환

private:
    int depth;  // 구덩이의 깊이
};

#endif // PITFALL_H
