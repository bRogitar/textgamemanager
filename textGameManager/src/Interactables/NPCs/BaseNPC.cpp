#include "BaseNPC.h"

BaseNPC::BaseNPC(const std::string& id, const std::string& name, const std::string& dialogue)
    : id(id), name(name), dialogue(dialogue), isInteractable(true) {}

std::string BaseNPC::getId() const {
    return id;
}

std::string BaseNPC::getName() const {
    return name;
}

std::string BaseNPC::getDialogue() const {
    return dialogue;
}

void BaseNPC::setDialogue(const std::string& newDialogue) {
    dialogue = newDialogue;
}

void BaseNPC::setName(const std::string& newName) {
    name = newName;
}

bool BaseNPC::canInteract(const Player* player) const {
    return isInteractable;
}
