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
    std::vector<std::string> getInteractionOptions(const IInteractable* interactable);

private:
    InteractionManager();
    ~InteractionManager() = default;
    InteractionManager(const InteractionManager&) = delete;
    InteractionManager& operator=(const InteractionManager&) = delete;
    void processDialogueAction(Player& player, BaseNPC* npc);
};

#endif // INTERACTIONMANAGER_H