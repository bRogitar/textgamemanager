// #ifndef INTERACTION_MANAGER_H
// #define INTERACTION_MANAGER_H

<<<<<<< HEAD
#include "Player.h"
#include "BaseNPC.h"
#include "BaseTrap.h"
<<<<<<< HEAD
#include "MonsterFactory.h"
#include "NPCFactory.h"
#include "TrapFactory.h"
#include "ActionResult.h"
#include "Option.h"
#include <vector>
=======
>>>>>>> c9dde9b632d118257875ad075c88ed21cca3f920

// InteractionManager 클래스 선언
class InteractionManager {
public:
    // 싱글톤 인스턴스를 얻기 위한 정적 메서드
    static InteractionManager& getInstance();
<<<<<<< HEAD
    
    // 기본 상호작용 처리
=======

    // NPC와의 상호작용 처리 함수
>>>>>>> c9dde9b632d118257875ad075c88ed21cca3f920
    void handleNPCInteraction(Player& player, BaseNPC* npc);

    // 함정과의 상호작용 처리 함수
    void handleTrapInteraction(Player& player, BaseTrap* trap);
<<<<<<< HEAD
    void handleMonsterInteraction(Player& player, BaseMonster* monster);
    
    // 액션 처리 시스템
    void processAction(const Option& option, Player& player);
    void applyActionResult(const ActionResult& result, Player& player);
    bool checkRequirements(const std::vector<Requirement>& requirements, const Player& player);
    
    // Factory 관련
    BaseMonster* createMonster(const std::string& type);
    BaseNPC* createNPC(const std::string& type);
    BaseTrap* createTrap(const std::string& type);
=======
>>>>>>> c9dde9b632d118257875ad075c88ed21cca3f920
=======
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
>>>>>>> 131a76a54a8f3dc29b3839d3d3f294c9da90065e

// private:
//     // 싱글톤을 위한 생성자 (private)
//     InteractionManager();

<<<<<<< HEAD
    // 복사 생성자와 대입 연산자를 삭제하여 싱글톤 보장
    InteractionManager(const InteractionManager&) = delete;
    InteractionManager& operator=(const InteractionManager&) = delete;
<<<<<<< HEAD

    MonsterFactory monsterFactory;
    NPCFactory npcFactory;
    TrapFactory trapFactory;
=======
>>>>>>> c9dde9b632d118257875ad075c88ed21cca3f920
};
=======
//     // 복사 생성자와 대입 연산자를 삭제하여 싱글톤 보장
//     InteractionManager(const InteractionManager&) = delete;
//     InteractionManager& operator=(const InteractionManager&) = delete;
// };
>>>>>>> 131a76a54a8f3dc29b3839d3d3f294c9da90065e

// #endif // INTERACTION_MANAGER_H
