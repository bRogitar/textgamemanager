#include "InteractionManager.h"

InteractionManager& InteractionManager::getInstance() {
    static InteractionManager instance;
    return instance;
}

InteractionManager::InteractionManager() {}

void InteractionManager::handleNPCInteraction(Player& player, BaseNPC* npc) {
    // NPC와의 상호작용 처리
    if (npc != nullptr && npc->canInteract(&player)) {
        npc->interact(&player);
    }
}

void InteractionManager::handleTrapInteraction(Player& player, BaseTrap* trap) {
    // 함정과의 상호작용 처리
    if (trap != nullptr) {
        trap->trigger(&player);
    }
}

void InteractionManager::handleShopInteraction(Player& player, Shopkeeper* shop) {
    // 상점과의 상호작용 처리
    if (shop != nullptr) {
        processTradeAction(player, shop);
    }
}

void InteractionManager::processTradeAction(Player& player, Shopkeeper* shop) {
    // 거래 처리
    std::cout << shop->getName() << "와(과) 거래를 시작합니다." << std::endl;
    // 거래 로직 구현
}
