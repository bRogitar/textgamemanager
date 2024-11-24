#include "GameManager.h"
#include "Event.h"
#include <iostream>
#include <algorithm>
#include "tinyxml2.h"
#include "MonsterFactory.h"
#include "CombatManager.h"
#include <filesystem>

using namespace tinyxml2;

// 싱글톤 패턴으로 GameManager 인스턴스를 반환
GameManager& GameManager::getInstance() {
    static GameManager instance;
    return instance;
}

// GameManager 생성자 - 월드 맵을 생성하고 초기화
GameManager::GameManager() : worldMap(createWorldMap()) {}

// 게임 초기화 - 플레이어와 월드 맵을 초기화
void GameManager::initializeGame() {
    std::cout << "Initializing game...";
    player = Player();
    player.setHealth(100);
    player.setMentalStrength(50);
    player.setAttackPower(20);
    player.setMoney(100);
    worldMap = createWorldMap();
}

// 게임 시작 메서드
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
            loadGame("savegame.xml");
        } else {
            displayMessage("Invalid choice. Please enter 1 or 2.\n");
        }
    }

    gameLoop();
}

// 게임 루프 - 방을 탐험하고 이벤트를 처리하는 메인 루프
void GameManager::gameLoop() {
    for (auto& room : worldMap) {
        if (!room.isCleared()) {
            displayMessage("You have entered " + room.getRoomName() + ".\n");
            displayMessage("Do you want to save your progress? (y/n): ");
            char saveChoice = getUserInput()[0];
            if (saveChoice == 'y' || saveChoice == 'Y') {
                saveGame("savegame.xml");
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

// 화면에 메시지를 출력하는 메서드
void GameManager::displayMessage(const std::string& message) {
    std::cout << message;
}

// 선택지 옵션을 출력하는 메서드
void GameManager::displayOptions(const std::vector<std::string>& options) {
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << i + 1 << ". " << options[i] << "\n";
    }
}

// 사용자 입력을 받아오는 메서드
std::string GameManager::getUserInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

// 전투를 시작하는 메서드
void GameManager::startCombat(BaseMonster enemy) {
    displayMessage("Combat started with " + enemy.getName() + "!\n");
}

// 게임을 XML 파일에 저장하는 메서드
void GameManager::saveGame(const std::string& filename) {
    XMLDocument doc;
    XMLNode* pRoot = doc.NewElement("GameSave");
    doc.InsertFirstChild(pRoot);

    // 플레이어 상태 저장
    XMLElement* pPlayer = doc.NewElement("PlayerStatus");
    pPlayer->SetAttribute("name", player.getName().c_str());
    pPlayer->SetAttribute("health", player.getHealth());
    pPlayer->SetAttribute("mentalStrength", player.getMentalStrength());
    pPlayer->SetAttribute("attackPower", player.getAttackPower());
    pPlayer->SetAttribute("money", player.getMoney());
    pRoot->InsertEndChild(pPlayer);

    // 방 상태 저장
    XMLElement* pRooms = doc.NewElement("Rooms");
    for (const auto& room : worldMap) {
        XMLElement* pRoom = doc.NewElement("Room");
        pRoom->SetAttribute("name", room.getRoomName().c_str());
        pRoom->SetAttribute("cleared", room.isCleared());
        pRooms->InsertEndChild(pRoom);
    }
    pRoot->InsertEndChild(pRooms);

    XMLError eResult = doc.SaveFile(filename.c_str());
    if (eResult != XML_SUCCESS) {
        displayMessage("Error saving game!\n");
    } else {
        displayMessage("Game saved successfully!\n");
    }
}

// 게임을 XML 파일에서 불러오는 ㅁ서드
void GameManager::loadGame(const std::string& filename) {
    XMLDocument doc;
    XMLError eResult = doc.LoadFile(filename.c_str());
    if (eResult != XML_SUCCESS) {
        displayMessage("Failed to load save file. Starting a new game instead...\n");
        return;
    }

    XMLNode* pRoot = doc.FirstChildElement("GameSave");
    if (pRoot == nullptr) {
        displayMessage("Invalid save file format. Starting a new game instead...\n");
        return;
    }

    // 플레이어 상태 로드
    XMLElement* pElement = pRoot->FirstChildElement("PlayerStatus");
    if (pElement != nullptr) {
        player.setName(pElement->Attribute("name") ? pElement->Attribute("name") : "Unknown");
        int health; pElement->QueryIntAttribute("health", &health); player.setHealth(health);
        int mentalStrength; pElement->QueryIntAttribute("mentalStrength", &mentalStrength); player.setMentalStrength(mentalStrength);
        int attackPower; pElement->QueryIntAttribute("attackPower", &attackPower); player.setAttackPower(attackPower);
        int money; pElement->QueryIntAttribute("money", &money); player.setMoney(money);
    }

    // 방 상태 로드
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

// 월드 맵을 XML 파일에서 불러오는 메서드
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

    // 각 방을 생성하여 월드 맵에 추가
    for (XMLElement* pRoom = pRooms->FirstChildElement("Room"); pRoom != nullptr; pRoom = pRoom->NextSiblingElement("Room")) {
        std::string roomId = pRoom->Attribute("id") ? pRoom->Attribute("id") : "Unknown";
        std::string roomName = pRoom->Attribute("name") ? pRoom->Attribute("name") : "Unknown";
        std::string description = pRoom->Attribute("description") ? pRoom->Attribute("description") : "";
        std::string eventId = pRoom->Attribute("eventId") ? pRoom->Attribute("eventId") : "";

        worldMap.emplace_back(roomId, roomName, description, eventId);
    }

    return worldMap;
}

// 이벤트 XML 파일을 로드하여 이벤트 객체를 생성하는 메서드
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

    // 이벤트 이름과 설명을 불러와서 Event 객체 생성
    std::string eventName = pEvent->FirstChildElement("name")->GetText() ? pEvent->FirstChildElement("name")->GetText() : "Unknown";
    std::string eventDescription = pEvent->FirstChildElement("description")->GetText() ? pEvent->FirstChildElement("description")->GetText() : "";
    Event event(eventId, eventName, eventDescription);

    // 몬스터 로드
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

    // 선택지 로드
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

// 저장된 파일 목록을 가져오는 메서드
std::vector<std::string> GameManager::getSaveFiles() const {
    std::vector<std::string> saveFiles;
    for (const auto& entry : std::filesystem::directory_iterator(SAVE_DIRECTORY)) {
        if (entry.is_regular_file()) {
            saveFiles.push_back(entry.path().filename().string());
        }
    }
    return saveFiles;
}
