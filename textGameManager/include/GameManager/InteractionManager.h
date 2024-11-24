#ifndef INTERACTIONMANAGER_H
#define INTERACTIONMANAGER_H

#include "Player.h"
#include "BaseNPC.h"
#include "BaseTrap.h"
#include <vector>

class InteractionManager {
public:
    static InteractionManager& getInstance();
    void handleNPCInteraction(Player& player, BaseNPC* npc);
    void handleTrapInteraction(Player& player, BaseTrap* trap);
    void handleShopInteraction(Player& player, Shopkeeper* shop);
    std::vector<std::string> getInteractionOptions(const IInteractable* interactable);

private:
    InteractionManager();
    ~InteractionManager() = default;
    InteractionManager(const InteractionManager&) = delete;
    InteractionManager& operator=(const InteractionManager&) = delete;

    void processTradeAction(Player& player, Shopkeeper* shop);
    void processDialogueAction(Player& player, BaseNPC* npc);
};

#endif // INTERACTIONMANAGER_H