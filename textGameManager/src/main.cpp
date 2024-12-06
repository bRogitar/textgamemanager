// main.cpp
#include "GameManager.h"

int main() {
    GameManager& gameManager = GameManager::getInstance();
    
    gameManager.initializeGame();
    gameManager.startGame();

    return 0;
}