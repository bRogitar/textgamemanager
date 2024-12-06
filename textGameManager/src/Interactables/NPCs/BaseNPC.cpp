//BaseNPC.cpp

#include "BaseNPC.h"
#include <iostream>

BaseNPC::BaseNPC(const std::string& name, const std::string& dialog)
    : name(name), dialog(dialog) {}

const std::string& BaseNPC::getName() const {
    return name;
}

const std::string& BaseNPC::getDialog() const {
    return dialog;
}

void BaseNPC::setAttributes(const std::string& newName, const std::string& newDialog) {
    name = newName;
    dialog = newDialog;
}