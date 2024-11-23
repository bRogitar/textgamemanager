#include "GameManager.h"
#include <iostream>
#include <algorithm>

GameManager& GameManager::getInstance() {
    static GameManager instance;
    return instance;
}

GameManager::GameManager() : worldMap(createWorldMap()) {}

void GameManager::initializeGame() {
    std::cout << "Initializing game...\n";
    player = Player();
    worldMap = createWorldMap();
}

void GameManager::startGame() {
    int choice = 0;
    bool validInput = false;

    while (!validInput) {
        displayMessage("===========================\n");
        displayMessage("       Text Game Manager      \n");
        displayMessage("===========================\n");
        displayMessage("1. New Game\n");
        displayMessage("2. Load Game\n");
        displayMessage("===========================\n");
        displayMessage("Select an option (1 or 2): ");
        choice = std::stoi(getUserInput());

        if (choice == 1) {
            displayMessage("Starting a new game...\n");
            validInput = true;
        } else if (choice == 2) {
            displayMessage("Loading saved game...\n");
            validInput = true;
            loadGame();
        } else {
            displayMessage("Invalid choice. Please enter 1 or 2.\n");
        }
    }

    gameLoop();
}

void GameManager::gameLoop() {
    for (auto& room : worldMap) {
        if (!room.isCleared()) {
            displayMessage("You have entered " + room.getRoomName() + ".\n");
            displayMessage("Do you want to save your progress? (y/n): ");
            char saveChoice = getUserInput()[0];
            if (saveChoice == 'y' || saveChoice == 'Y') {
                saveGame();
            }

            if (room.hasEvent()) {
                displayMessage("An event is happening in " + room.getRoomName() + "...\n");
                // Event logic goes here
                // Placeholder for monster battle or other interactions
                room.setCleared(true); 
            }
        }
    }

    displayMessage("Congratulations! You have completed all rooms. The game is now over.\n");
}

void GameManager::displayMessage(const std::string& message) {
    std::cout << message;
}

void GameManager::displayOptions(const std::vector<std::string>& options) {
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i + 1 << ". " << options[i] << "\n";
    }
}

std::string GameManager::getUserInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void GameManager::startCombat(BaseMonster enemy) {
    // Combat logic will be implemented here
    displayMessage("Combat started with " + enemy.getName() + "!\n");
}

void GameManager::saveGame() {
    XMLDocument doc;
    XMLNode* pRoot = doc.NewElement("GameSave");
    doc.InsertFirstChild(pRoot);

    XMLElement* pPlayer = doc.NewElement("PlayerStatus");
    pPlayer->SetAttribute("name", player.name.c_str());
    pPlayer->SetAttribute("strength", player.strength);
    pPlayer->SetAttribute("health", player.health);
    pRoot->InsertEndChild(pPlayer);

    XMLElement* pRooms = doc.NewElement("Rooms");
    for (const auto& room : worldMap) {
        XMLElement* pRoom = doc.NewElement("Room");
        pRoom->SetAttribute("name", room.getRoomName().c_str());
        pRoom->SetAttribute("cleared", room.isCleared());
        pRooms->InsertEndChild(pRoom);
    }
    pRoot->InsertEndChild(pRooms);

    XMLError eResult = doc.SaveFile("savegame.xml");
    if (eResult != XML_SUCCESS) {
        displayMessage("Error saving game!\n");
    } else {
        displayMessage("Game saved successfully!\n");
    }
}

void GameManager::loadGame() {
    XMLDocument doc;
    XMLError eResult = doc.LoadFile("savegame.xml");
    if (eResult != XML_SUCCESS) {
        displayMessage("Failed to load save file. Starting a new game instead...\n");
        return;
    }

    XMLNode* pRoot = doc.FirstChildElement("GameSave");
    if (pRoot == nullptr) {
        displayMessage("Invalid save file format. Starting a new game instead...\n");
        return;
    }

    XMLElement* pElement = pRoot->FirstChildElement("PlayerStatus");
    if (pElement != nullptr) {
        player.name = pElement->Attribute("name") ? pElement->Attribute("name") : "Unknown";
        pElement->QueryIntAttribute("strength", &player.strength);
        pElement->QueryIntAttribute("health", &player.health);
    }

    XMLElement* pRooms = pRoot->FirstChildElement("Rooms");
    if (pRooms != nullptr) {
        for (XMLElement* pRoom = pRooms->FirstChildElement("Room"); pRoom != nullptr; pRoom = pRoom->NextSiblingElement("Room")) {
            std::string roomName = pRoom->Attribute("name") ? pRoom->Attribute("name") : "Unknown";
            bool cleared;
            pRoom->QueryBoolAttribute("cleared", &cleared);
            for (auto& room : worldMap) {
                if (room.getRoomName() == roomName) {
                    room.setCleared(true); 
                }
            }
        }
    }

    displayMessage("Loaded player: " + player.name + ", Strength: " + std::to_string(player.strength) + ", Health: " + std::to_string(player.health) + "\n");
}

std::vector<Room> GameManager::createWorldMap() {
    std::vector<Room> worldMap;
    for (int i = 1; i <= 8; ++i) {
        worldMap.emplace_back("Room " + std::to_string(i), true);
    }
    return worldMap;
}
