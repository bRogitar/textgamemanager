// main.cpp
#include "GameManager.h"
#include <iostream>
#include <locale>

int main() {
    std::wcout.imbue(std::locale());

    GameManager& gameManager = GameManager::getInstance();
    gameManager.initializeGame();
    gameManager.startGame();

    return 0;
}
