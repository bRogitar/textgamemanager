#include "GameManager.h"
#include <iostream>
#include <algorithm>
#include "tinyxml2.h"

using namespace tinyxml2;

GameManager& GameManager::getInstance() {
    static GameManager instance;
    return instance;
}

GameManager::GameManager() : worldMap(createWorldMap()) {}

void GameManager::initializeGame() {
    std::cout << "Initializing game...";
    player = Player();
    player.setHealth(100);
    player.setMentalStrength(50);
    player.setAttackPower(20);
    player.setMoney(100);
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
                bool cleared = true;
                room.setCleared(cleared); 
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
    pPlayer->SetAttribute("name", player.getName().c_str());
    pPlayer->SetAttribute("health", player.getHealth());
    pPlayer->SetAttribute("mentalStrength", player.getMentalStrength());
    pPlayer->SetAttribute("attackPower", player.getAttackPower());
    pPlayer->SetAttribute("money", player.getMoney());
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
        player.setName(pElement->Attribute("name") ? pElement->Attribute("name") : "Unknown");
        int health; pElement->QueryIntAttribute("health", &health); player.setHealth(health);
        int mentalStrength; pElement->QueryIntAttribute("mentalStrength", &mentalStrength); player.setMentalStrength(mentalStrength);
        int attackPower; pElement->QueryIntAttribute("attackPower", &attackPower); player.setAttackPower(attackPower);
        int money; pElement->QueryIntAttribute("money", &money); player.setMoney(money);
    }

    XMLElement* pRooms = pRoot->FirstChildElement("Rooms");
    if (pRooms != nullptr) {
        for (XMLElement* pRoom = pRooms->FirstChildElement("Room"); pRoom != nullptr; pRoom = pRoom->NextSiblingElement("Room")) {
            std::string roomName = pRoom->Attribute("name") ? pRoom->Attribute("name") : "Unknown";
            bool cleared;
            pRoom->QueryBoolAttribute("cleared", &cleared);
            for (auto& room : worldMap) {
                if (room.getRoomName() == roomName) {
                    room.setCleared(cleared); 
                }
            }
        }
    }

    displayMessage("Loaded player: " + player.getName() + ", Health: " + std::to_string(player.getHealth()) + ", Mental Strength: " + std::to_string(player.getMentalStrength()) + ", Attack Power: " + std::to_string(player.getAttackPower()) + ", Money: " + std::to_string(player.getMoney()));
}

std::vector<Room> GameManager::createWorldMap() {
    std::vector<Room> worldMap;
    XMLDocument doc;
    XMLError eResult = doc.LoadFile("resource/worldmap.xml");
    if (eResult != XML_SUCCESS) {
        displayMessage("Error loading world map from XML file!\n");
        return worldMap;
    }

    XMLElement* pRooms = doc.FirstChildElement("WorldMap")->FirstChildElement("Rooms");
    if (pRooms == nullptr) {
        displayMessage("No rooms found in XML file!\n");
        return worldMap;
    }

    for (XMLElement* pRoom = pRooms->FirstChildElement("Room"); pRoom != nullptr; pRoom = pRoom->NextSiblingElement("Room")) {
        std::string roomId = pRoom->Attribute("id") ? pRoom->Attribute("id") : "Unknown";
        std::string roomName = pRoom->Attribute("name") ? pRoom->Attribute("name") : "Unknown";
        std::string description = pRoom->Attribute("description") ? pRoom->Attribute("description") : "";
        bool hasEvent = false;
        pRoom->QueryBoolAttribute("event", &hasEvent);
        
        worldMap.emplace_back(roomId, roomName, description);
    }

    return worldMap;
}
