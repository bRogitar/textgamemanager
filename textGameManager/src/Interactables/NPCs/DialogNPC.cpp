#include "DialogNPC.h"
#include "NPCTrapRegistration.h"
#include <iostream>

DialogNPC::DialogNPC(const std::string& name, const std::string& dialog)
    : BaseNPC(name, dialog) {}

void DialogNPC::interact(Player& player) {
    std::cout << getName() << ": " << getDialog() << std::endl;
}

std::unique_ptr<BaseNPC> DialogNPC::clone() const {
    return std::make_unique<DialogNPC>(*this);
}

// NPC 등록
REGISTER_NPC(DialogNPC);