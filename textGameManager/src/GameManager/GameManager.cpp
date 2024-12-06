#include "GameManager.h"
#include "Event.h"
#include "EventManager.h"
#include "InputManager.h"  // InputManager 헤더 추가
#include <iostream>
#include <algorithm>
#include "tinyxml2.h"
#include "MonsterFactory.h"
#include "CombatManager.h"
#include <filesystem>

using namespace tinyxml2;

GameManager& GameManager::getInstance() {
    static GameManager instance;
    return instance;
}

GameManager::GameManager() : worldMap(createWorldMap()) {}

void GameManager::initializeGame() {
    std::cout << "Initializing game...\n";

    // 기존 Player 객체의 상태를 초기화 (이름 유지)
    player.setHealth(100);
    player.setMentalStrength(50);
    player.setAttackPower(20);
    player.setMoney(100);

    // 월드 맵 초기화
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
        displayMessage("3. Delete Save File\n");
        displayMessage("===========================\n");
        displayMessage("Select an option (1, 2, or 3): ");
        std::string input = InputManager::getInstance()->getUserInput();

        try {
            choice = std::stoi(input);
        } catch (std::invalid_argument&) {
            displayMessage("Invalid choice. Please enter 1, 2, or 3.\n");
            continue;
        }

        if (choice == 1) {
            displayMessage("Starting a new game...\n");
            displayMessage("Enter your player's name: ");
            std::string playerName = InputManager::getInstance()->getUserInput();
            player.setName(playerName); // 이름 설정

            initializeGame(); // 초기화 함수는 이름 설정 이후에 호출
            validInput = true;
            displayPlayerStatus(); // 플레이어 상태 표시
        } else if (choice == 2) {
            displayMessage("Loading saved game...\n");
            displaySaveFiles();  // 저장된 파일 목록을 표시
            displayMessage("Enter the save file name to load: ");
            std::string loadFileName = InputManager::getInstance()->getUserInput();
            loadGame(loadFileName); // 저장된 파일 이름을 사용해 게임 로드
            validInput = true;
            displayPlayerStatus(); // 게임 로드 후 플레이어 상태 표시
        } else if (choice == 3) {
            displayMessage("Deleting a saved file...\n");
            displaySaveFiles();  // 저장된 파일 목록을 표시
            displayMessage("Enter the save file name to delete: ");
            std::string deleteFileName = InputManager::getInstance()->getUserInput();
            if (deleteSaveFile(deleteFileName)) {
                displayMessage("Save file deleted successfully.\n");
            } else {
                displayMessage("Failed to delete save file. File may not exist.\n");
            }
        } else {
            displayMessage("Invalid choice. Please enter 1, 2, or 3.\n");
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

void GameManager::startCombat(BaseMonster& enemy) {
    // 전투 로직 구현
    displayMessage("Combat started with " + enemy.getName() + "!\n");

    // 실제 전투 로직 호출하기
    CombatManager combat(player, &enemy); // 포인터로 전달
    combat.startCombat();
}

#include <filesystem>  // std::filesystem 사용을 위한 헤더 파일 추가
namespace fs = std::filesystem;

bool GameManager::deleteSaveFile(const std::string& saveFileName) {
    std::string savePath = "save/" + saveFileName;

    try {
        if (fs::exists(savePath)) {
            fs::remove(savePath);
            return true;
        } else {
            return false;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error deleting file: " << e.what() << std::endl;
        return false;
    }
}

void GameManager::saveGame(const std::string& saveFileName) {
    // "save" 디렉터리 생성
    fs::create_directories("save");
    std::string savePath = "save/" + saveFileName;

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

    XMLError eResult = doc.SaveFile(savePath.c_str());
    if (eResult != XML_SUCCESS) {
        displayMessage("Error saving game!\n");
    } else {
        displayMessage("Game saved successfully to " + savePath + "\n");
    }
}

void GameManager::loadGame(const std::string& loadFileName) {
    std::string loadPath = "save/" + loadFileName;

    XMLDocument doc;
    XMLError eResult = doc.LoadFile(loadPath.c_str());
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

void GameManager::displaySaveFiles() {
    displayMessage("\n===========================\n");
    displayMessage("     Available Saves     \n");
    displayMessage("===========================\n\n");

    if (!fs::exists("save") || fs::is_empty("save")) {
        displayMessage("No save files found.\n");
        return;
    }

    for (const auto& entry : fs::directory_iterator("save")) {
        if (entry.is_regular_file()) {
            displayMessage("► " + entry.path().filename().string() + "\n");
        }
    }
    displayMessage("\n===========================\n");
}

std::vector<Room> GameManager::createWorldMap() {
    std::vector<Room> worldMap;
    XMLDocument doc;

    std::cout << "Loading world map from: resources/worldmap.xml" << std::endl;
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
        newRoom.setCleared(false);
        worldMap.push_back(newRoom);

        std::cout << "Loaded Room: " << roomName << ", ID: " << roomId << ", Event ID: " << eventId << std::endl;
    }

    return worldMap;
}

void GameManager::useAbility() {
    // 현재 플레이어의 어빌리티 목록 표시
    player.displayAbilities();

    // 플레이어에게 사용하고자 하는 어빌리티의 ID 입력 요청
    std::cout << "Enter the ability ID to use: ";
    std::string abilityId = InputManager::getInstance()->getUserInput(); // getUserInput 사용

    // Player 클래스의 useAbility 함수 호출을 통해 처리
    player.useAbility(abilityId);
}

void GameManager::gameLoop() {
    size_t currentRoomIndex = 0;

    while (currentRoomIndex < worldMap.size()) {
        Room& currentRoom = worldMap[currentRoomIndex];

        displayMessage("\n===========================");
        displayMessage("\nEntering room: " + currentRoom.getRoomName() + "\n");

        // 저장 기능
        bool validInput = false;
        while (!validInput) {
            displayMessage("Would you like to save your progress? (yes/no): ");
            std::string saveChoice = InputManager::getInstance()->getUserInput();

            if (saveChoice == "yes" || saveChoice == "y") {
                displayMessage("Enter save file name: ");
                std::string saveFileName = InputManager::getInstance()->getUserInput();
                saveGame(saveFileName);
                validInput = true;
            } else if (saveChoice == "no" || saveChoice == "n") {
                validInput = true;
            } else {
                displayMessage("Invalid choice. Please enter 'yes' or 'no'.");
            }
        }

        // 어빌리티 체크
        validInput = false;
        while (!validInput) {
            displayMessage("Would you like to check and use an ability from your inventory? (yes/no): ");
            std::string abilityChoice = InputManager::getInstance()->getUserInput();

            if (abilityChoice == "yes" || abilityChoice == "y") {
                useAbility();
                validInput = true;
            } else if (abilityChoice == "no" || abilityChoice == "n") {
                validInput = true;
            } else {
                displayMessage("Invalid choice. Please enter 'yes' or 'no'.");
            }
        }

        // 이벤트 처리
        if (currentRoom.hasEvent()) {
            EventManager& eventManager = EventManager::getInstance();
            std::string result = eventManager.processEvent(currentRoom.getEventId(), player);

            // end 이벤트 처리
            if (result == "end") {
                displayMessage("\n===========================");
                displayMessage("Congratulations! You have completed your journey!");
                displayMessage("===========================\n");
                return;  // 게임 즉시 종료
            }
        }

        // 룸 클리어 처리 및 다음 룸으로 이동
        currentRoom.setCleared(true);
        displayMessage("\nRoom: " + currentRoom.getRoomName() + " has been cleared.");

        currentRoomIndex++;

        if (currentRoomIndex < worldMap.size()) {
            displayMessage("\n===========================");
            displayMessage("\nMoving to the next room...");
        }
    }

    // 모든 룸을 클리어한 경우 메시지 출력
    displayMessage("\n===========================");
    displayMessage("All rooms have been explored.");
    displayMessage("You have completed your journey!");
    displayMessage("===========================\n");
}






