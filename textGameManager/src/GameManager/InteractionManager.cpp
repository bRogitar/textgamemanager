// #include "InteractionManager.h"

// InteractionManager& InteractionManager::getInstance() {
//     static InteractionManager instance;
//     return instance;
// }

// InteractionManager::InteractionManager() {}

// void InteractionManager::handleNPCInteraction(Player& player, BaseNPC* npc) {
//     // NPC와의 상호작용 처리
//     if (npc != nullptr && npc->canInteract(&player)) {
//         npc->interact(&player);
//     }
// }

// void InteractionManager::handleTrapInteraction(Player& player, BaseTrap* trap) {
//     // 함정과의 상호작용 처리
//     if (trap != nullptr) {
//         trap->trigger(&player);
//     }
// }
