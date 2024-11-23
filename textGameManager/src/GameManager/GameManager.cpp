#include "GameManager.h"
#include "Event.h"
#include <iostream>
#include <algorithm>
#include "tinyxml2.h"
#include "MonsterFactory.h"
#include "CombatManager.h"

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
                Event event = loadEvent(room.getEventId());
                event.execute(player);
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

void GameManager::displayMessage(const std::string& message) {
    std::cout << message << std::endl;
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
        std::string eventId = pRoom->Attribute("eventId") ? pRoom->Attribute("eventId") : "";
        
        worldMap.emplace_back(roomId, roomName, description, eventId);
    }

    return worldMap;
}

MonsterFactory monsterFactory;

Event GameManager::loadEvent(const std::string& eventId) {
    XMLDocument doc;
    std::string filePath = "resource/events/" + eventId + ".xml";
    XMLError eResult = doc.LoadFile(filePath.c_str());
    if (eResult != XML_SUCCESS) {
        displayMessage("Error loading event file: " + filePath + "\n");
    }

    XMLElement* pEvent = doc.FirstChildElement("Event");
    if (pEvent == nullptr) {
        displayMessage("Invalid event file format: " + filePath + "\n");
    }

    std::string eventName = pEvent->FirstChildElement("name")->GetText() ? pEvent->FirstChildElement("name")->GetText() : "Unknown";
    std::string eventDescription = pEvent->FirstChildElement("description")->GetText() ? pEvent->FirstChildElement("description")->GetText() : "";
    Event event(eventId, eventName, eventDescription);

    // Load Monster from XML
    XMLElement* pMonster = pEvent->FirstChildElement("Monster");
    if (pMonster != nullptr) {
        std::string monsterType = pMonster->Attribute("name") ? pMonster->Attribute("name") : "Unknown";
        int health = 0;
        int attackPower = 0;
        pMonster->QueryIntAttribute("health", &health);
        pMonster->QueryIntAttribute("attackPower", &attackPower);

        auto monster = MonsterFactory::createMonster(monsterType, health, attackPower);
        if (monster != nullptr) {
            event.setMonster(std::move(monster));
        }
    }

    // Load Choices from XML
    XMLElement* pChoices = pEvent->FirstChildElement("Choices");
    if (pChoices != nullptr) {
        for (XMLElement* pChoice = pChoices->FirstChildElement("Choice"); pChoice != nullptr; pChoice = pChoice->NextSiblingElement("Choice")) {
            std::string choiceId = pChoice->Attribute("id") ? pChoice->Attribute("id") : "Unknown";
            std::string description = pChoice->Attribute("description") ? pChoice->Attribute("description") : "";
            int healthImpact = 0, mentalStrengthImpact = 0, attackPowerImpact = 0, moneyImpact = 0;

            pChoice->QueryIntAttribute("healthImpact", &healthImpact);
            pChoice->QueryIntAttribute("mentalStrengthImpact", &mentalStrengthImpact);
            pChoice->QueryIntAttribute("attackPowerImpact", &attackPowerImpact);
            pChoice->QueryIntAttribute("moneyImpact", &moneyImpact);

            Choice choice(choiceId, description, healthImpact, mentalStrengthImpact, attackPowerImpact, moneyImpact);
            event.addChoice(choice);
        }
    }

    return event;
}
void GameManager::gameLoop() {
    for (auto& room : worldMap) {
        if (!room.isCleared()) {
            displayMessage("You have entered " + room.getRoomName() + ".\n");
            if (room.hasEvent()) {
                Event event = loadEvent(room.getEventId());

                if (event.hasMonster()) {
                    BaseMonster* monster = event.getMonster();
                    CombatManager combat(player, *monster);
                    combat.startCombat();

                    if (player.isDefeated()) {
                        displayMessage("You have been defeated. Returning to starting point with penalties...\n");
                        player.applyDefeatPenalty();
                        return; // 종료 혹은 리셋 처리
                    } else {
                        displayMessage("You defeated the monster!\n");
                    }
                }

                event.displayChoices();
                int choice = std::stoi(getUserInput());
                event.executeChoice(choice - 1, player);
            }
            room.setCleared(true);
        }
    }

    displayMessage("Congratulations! You have completed all rooms. The game is now over.\n");
}
