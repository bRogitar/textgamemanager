#include "BaseNPC.h"

BaseNPC::BaseNPC(const std::string& id, const std::string& name, const std::string& dialogue)
    : id(id), name(name), dialogue(dialogue) {}

std::string BaseNPC::getId() const {
    return id;
}

std::string BaseNPC::getName() const {
    return name;
}

std::string BaseNPC::getDialogue() const {
    return dialogue;
}
