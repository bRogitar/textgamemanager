//NPCFactory.cpp

#include "NPCFactory.h"

std::unordered_map<std::string, std::unique_ptr<BaseNPC>> NPCFactory::prototypes;

std::unique_ptr<BaseNPC> NPCFactory::createNPC(const std::string& type, const std::string& name, const std::string& dialog) {
    auto it = prototypes.find(type);
    if (it != prototypes.end()) {
        auto npc = it->second->clone();
        npc->setAttributes(name, dialog);
        return npc;
    }
    return nullptr;
}

void NPCFactory::registerPrototype(const std::string& type, std::unique_ptr<BaseNPC> prototype) {
    prototypes[type] = std::move(prototype);
}