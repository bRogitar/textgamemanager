#include "GameManager.h"
#include "Event.h"
#include "EventManager.h"
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
    std::cout << "Initializing game...\n";
    player = Player();

    // 플레이어 이름 설정
    displayMessage("Enter your player's name: ");
    std::string playerName = getUserInput();
    player.setName(playerName);

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
            initializeGame(); // 플레이어 이름 설정 포함
            validInput = true;
            displayPlayerStatus(); // 게임 시작 시 플레이어 상태 표시
        } else if (choice == 2) {
            displayMessage("Loading saved game...\n");
            validInput = true;
            loadGame();
            displayPlayerStatus(); // 게임 로드 후 플레이어 상태 표시
        } else {
            displayMessage("Invalid choice. Please enter 1 or 2.\n");
        }
    }

    gameLoop();
}

void GameManager::displayPlayerStatus() {
    displayMessage("===========================\n");
    displayMessage("Player Status:\n");
    displayMessage("Name: " + player.getName() + "\n");
    displayMessage("Health: " + std::to_string(player.getHealth()) + "\n");
    displayMessage("Mental Strength: " + std::to_string(player.getMentalStrength()) + "\n");
    displayMessage("Attack Power: " + std::to_string(player.getAttackPower()) + "\n");
    displayMessage("Money: " + std::to_string(player.getMoney()) + "\n");
    displayMessage("===========================\n");
}

void GameManager::displayMessage(const std::string& message) {
    std::cout << message << std::endl;
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

void GameManager::startCombat(BaseMonster& enemy) {
    // 전투 로직 구현
    displayMessage("Combat started with " + enemy.getName() + "!\n");

    // 실제 전투 로직 호출하기
    CombatManager combat(player, &enemy); // 포인터로 전달
    combat.startCombat();
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

    std::cout << "Loading world map from: resources/worldmap.xml" << std::endl; // 디버깅 메시지
    XMLError eResult = doc.LoadFile("../resources/worldmap.xml");
    if (eResult != XML_SUCCESS) {
        std::cout << "Error: Unable to load world map. Error code: " << eResult << std::endl;
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

        Room newRoom(roomId, roomName, description, eventId);
        newRoom.setCleared(false); // 모든 방은 처음에 클리어되지 않은 상태로 설정합니다.
        worldMap.push_back(newRoom);

        // 로드된 방 정보 출력 (디버깅용)
        std::cout << "Loaded Room: " << roomName << ", ID: " << roomId << ", Event ID: " << eventId << std::endl;
    }

    return worldMap;
}

void GameManager::gameLoop() {
    bool allRoomsCleared = false;

    while (!allRoomsCleared) {
        allRoomsCleared = true; // 초기값을 true로 설정한 후 모든 방을 확인

        for (auto& room : worldMap) {
            if (!room.isCleared()) {
                allRoomsCleared = false; // 클리어되지 않은 방이 있다면 false로 변경
                
                // 방에 들어가는 메시지 출력 (디버깅용)
                displayMessage("Entering room: " + room.getRoomName() + "\n");
                
                if (room.hasEvent()) {
                    EventManager& eventManager = EventManager::getInstance();
                    eventManager.processEvent(room.getEventId(), player);  // 이벤트 실행
                    
                    // 이벤트 처리 후 선택지 실행
                    Event* currentEvent = eventManager.getEvent(room.getEventId());
                    if (currentEvent != nullptr) {
                        currentEvent->displayChoices();
                        int choice = std::stoi(getUserInput());
                        eventManager.executeChoice(choice - 1, currentEvent, player);
                    }
                }

                room.setCleared(true); // 이벤트가 끝나면 방을 클리어 처리
            }
        }

        if (allRoomsCleared) {
            displayMessage("Congratulations! You have completed all rooms. The game is now over.\n");
        } else {
            displayMessage("There are still rooms to explore...\n");
        }
    }
}
