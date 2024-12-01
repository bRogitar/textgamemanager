#include "GameManager.h"
#include "Event.h"
#include "EventManager.h"
#include <iostream>
#include <algorithm>
#include "tinyxml2.h"
#include "MonsterFactory.h"
#include "CombatManager.h"
#include "Traps/BaseTrap.h"
#include "BaseNPC.h"
using namespace tinyxml2;

GameManager& GameManager::getInstance() {
    static GameManager instance;
    return instance;
}

GameManager::GameManager() : worldMap(createWorldMap()) {}

void GameManager::initializeGame() {
    std::cout << "게임 초기화 중...\n";

    // 기존 Player 객체의 상태를 초기화 (이름 유지)
    player.setHealth(100);
    player.setMentalStrength(50);
    player.setAttackPower(20);
    player.setMoney(100);
    player.clearAbilities();     // 어빌리티 초기화
    
    // 기본 어빌리티 추가 (필요한 경우)
    // auto startingAbility = AbilityFactory::createAbility("strength");
    // if (startingAbility) {
    //     player.addAbility(*startingAbility);
    // }

    // 월드 맵 초기화
    worldMap = createWorldMap();
}

void GameManager::handleTrapInteraction(Player& player, BaseTrap* trap) {
    if (trap != nullptr) {
        // 플레이어가 세계함정도감을 소유한 경우 함정을 해체할 수 있는지 확인
        if (player.hasAbility("trap_codex") && trap->canAvoid(&player)) {
            std::cout << "You successfully disarmed the trap using the World Trap Codex!" << std::endl;
            trap->reset(); // 트랩 해체
        } else if (trap->canAvoid(&player)) {
            std::cout << "You avoided the trap!" << std::endl;
        } else {
            std::cout << "The trap was triggered! You take damage." << std::endl;
            player.modifyHealth(-trap->getDamage());
        }
    }
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
    displayMessage("Enter your player's name: ");
    std::string playerName = getUserInput();
    player.setName(playerName); // 이름 설정

    initializeGame(); // 초기화 함수는 이름 설정 이후에 호출
    validInput = true;
    displayPlayerStatus(); // 플레이어 상태 표시
}
 else if (choice == 2) {
            displayMessage("Loading saved game...\n");
            loadGame();
            validInput = true;
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
    // 보유 어빌리티 표시 추가
    displayMessage("Abilities:\n");
    for (const auto& ability : player.getAbilityInventory().getAbilities()) {
        displayMessage("- " + ability.getName() + "\n");
    }
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

//게임 저장
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

    // 어빌리티 저장
    XMLElement* pAbilities = doc.NewElement("Abilities");
    for (const auto& ability : player.getAbilityInventory().getAbilities()) {
        XMLElement* pAbility = doc.NewElement("Ability");
        pAbility->SetAttribute("id", ability.getId().c_str());
        pAbilities->InsertEndChild(pAbility);
    }
    pPlayer->InsertEndChild(pAbilities);
    pRoot->InsertEndChild(pPlayer);

    XMLError eResult = doc.SaveFile("savegame.xml");
    if (eResult != XML_SUCCESS) {
        displayMessage("게임 저장 실패!\n");
        return;
    }
    displayMessage("게임 저장 성공!\n");
}

void GameManager::loadGame() {
    XMLDocument doc;
    XMLError eResult = doc.LoadFile("savegame.xml");
    if (eResult != XML_SUCCESS) {
        displayMessage("Failed to load save file. Starting a new game instead...\n");
        return;
    }

    XMLElement* pElement = doc.FirstChildElement("GameSave")->FirstChildElement("PlayerStatus");
    if (pElement != nullptr) {
        // 기본 스탯 복원
        player.setName(pElement->Attribute("name"));
        player.setHealth(pElement->IntAttribute("health"));
        player.setMentalStrength(pElement->IntAttribute("mentalStrength"));
        player.setAttackPower(pElement->IntAttribute("attackPower"));
        player.setMoney(pElement->IntAttribute("money"));

        // 어빌리티 복원
        player.clearAbilities();
        XMLElement* pAbilities = pElement->FirstChildElement("Abilities");
        if (pAbilities != nullptr) {
            for (XMLElement* pAbility = pAbilities->FirstChildElement("Ability");
                 pAbility != nullptr;
                 pAbility = pAbility->NextSiblingElement("Ability")) {
                
                const char* id = pAbility->Attribute("id");
                if (id) {
                    auto newAbility = AbilityFactory::createAbility(id);
                    if (newAbility) {
                        player.addAbility(*newAbility);
                    }
                }
            }
        }
    }
    
    displayMessage("Game loaded successfully!\n");
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
    while (true) {
        bool allRoomsCleared = true;

        for (auto& room : worldMap) {
            if (!room.isCleared()) {
                allRoomsCleared = false;

                displayMessage("Entering room: " + room.getRoomName() + "\n");

                if (room.hasEvent()) {
                    EventManager& eventManager = EventManager::getInstance();
                    eventManager.processEvent(room.getEventId(), player);
                }

                // 방을 "cleared" 상태로 설정
                room.setCleared(true);
            }
        }

        // 모든 방 상태를 디버깅 메시지로 출력
        for (const auto& room : worldMap) {
            std::cout << "Room: " << room.getRoomName() 
                      << " | Cleared: " << (room.isCleared() ? "true" : "false") << "\n";
        }

        // 모든 방이 클리어되었는지 확인
        if (allRoomsCleared) {
            displayMessage("Congratulations! You have completed all rooms. The game is now over.\n");
            break;
        } else {
            displayMessage("There are still rooms to explore...\n");
        }
    }
}
