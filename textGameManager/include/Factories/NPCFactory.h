#ifndef NPCFACTORY_H
#define NPCFACTORY_H

#include <memory>
#include "BaseNPC.h"
#include "Shopkeeper.h"
#include "QuestGiver.h"

class NPCFactory {
public:
    static std::unique_ptr<BaseNPC> createNPC(const std::string& type, 
        const std::string& id, const std::string& name, const std::string& dialogue);
};

#endif // NPCFACTORY_H 