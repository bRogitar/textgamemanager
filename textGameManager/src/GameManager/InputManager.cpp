#include "InputManager.h"
#include <iostream>

InputManager& InputManager::getInstance() {
    static InputManager instance;
    return instance;
}

std::string InputManager::getUserInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}