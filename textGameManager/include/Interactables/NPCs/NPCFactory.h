//NPCFactory.h

#ifndef NPCFACTORY_H
#define NPCFACTORY_H

#include <string>
#include <memory>
#include <unordered_map>
#include "BaseNPC.h"

class NPCFactory {
public:
    static std::unique_ptr<BaseNPC> createNPC(const std::string& type, 
        const std::string& name, const std::string& dialog);
    static void registerPrototype(const std::string& type, 
        std::unique_ptr<BaseNPC> prototype);

private:
    static std::unordered_map<std::string, std::unique_ptr<BaseNPC>> prototypes;
};

#endif