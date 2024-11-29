// #ifndef INTERACTION_MANAGER_H
// #define INTERACTION_MANAGER_H

// #include "Player.h"
// #include "BaseNPC.h"
// #include "BaseTrap.h"

// // InteractionManager 클래스 선언
// class InteractionManager {
// public:
//     // 싱글톤 인스턴스를 얻기 위한 정적 메서드
//     static InteractionManager& getInstance();

//     // NPC와의 상호작용 처리 함수
//     void handleNPCInteraction(Player& player, BaseNPC* npc);

//     // 함정과의 상호작용 처리 함수
//     void handleTrapInteraction(Player& player, BaseTrap* trap);

// private:
//     // 싱글톤을 위한 생성자 (private)
//     InteractionManager();

//     // 복사 생성자와 대입 연산자를 삭제하여 싱글톤 보장
//     InteractionManager(const InteractionManager&) = delete;
//     InteractionManager& operator=(const InteractionManager&) = delete;
// };

// #endif // INTERACTION_MANAGER_H
