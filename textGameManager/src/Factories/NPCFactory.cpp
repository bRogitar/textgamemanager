#include "NPCFactory.h"

std::unique_ptr<BaseNPC> NPCFactory::createNPC(
    const std::string& type, const std::string& id,
    const std::string& name, const std::string& dialogue) {
    
    if (type == "Shopkeeper") {
        return std::make_unique<Shopkeeper>(id, name, dialogue);
    }
    else if (type == "QuestGiver") {
        return std::make_unique<QuestGiver>(id, name, dialogue);
    }
    // else if (type == "Merchant") {
    //     return std::make_unique<Merchant>(id, name, dialogue);
    // }
    return nullptr;
} 