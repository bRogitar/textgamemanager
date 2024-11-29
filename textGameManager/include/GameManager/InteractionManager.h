#ifndef INTERACTIONMANAGER_H
#define INTERACTIONMANAGER_H

#include "Player.h"
#include "BaseNPC.h"
#include "BaseTrap.h"
#include "MonsterFactory.h"
#include "NPCFactory.h"
#include "TrapFactory.h"
#include "ActionResult.h"
#include "Option.h"
#include <vector>

class InteractionManager {
public:
    static InteractionManager& getInstance();
    
    // 기본 상호작용 처리
    void handleNPCInteraction(Player& player, BaseNPC* npc);
    void handleTrapInteraction(Player& player, BaseTrap* trap);
    void handleMonsterInteraction(Player& player, BaseMonster* monster);
    
    // 액션 처리 시스템
    void processAction(const Option& option, Player& player);
    void applyActionResult(const ActionResult& result, Player& player);
    bool checkRequirements(const std::vector<Requirement>& requirements, const Player& player);
    
    // Factory 관련
    BaseMonster* createMonster(const std::string& type);
    BaseNPC* createNPC(const std::string& type);
    BaseTrap* createTrap(const std::string& type);

private:
    InteractionManager();
    ~InteractionManager() = default;
    InteractionManager(const InteractionManager&) = delete;
    InteractionManager& operator=(const InteractionManager&) = delete;

    MonsterFactory monsterFactory;
    NPCFactory npcFactory;
    TrapFactory trapFactory;
};

#endif // INTERACTIONMANAGER_H