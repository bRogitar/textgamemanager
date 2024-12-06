#include "Event.h"
#include <iostream>
#include <limits>
#include "CombatManager.h"
#include <algorithm>
#include "EventManager.h"
#include "InputDecorator.h"  

// 선택지를 화면에 표시하는 함수
void Event::displayChoices() const {
    for (const auto& choice : choices) {
        std::cout << choice.getId() << ": " << choice.getDescription() << std::endl;
    }
}

void Event::execute(Player& player) {
    std::cout << description << "\n";
    displayChoices();

    InputManager* inputManager = InputManager::getInstance();
    InputDecorator inputDecorator(inputManager);

    while (true) {
        std::cout << "Enter your choice ID: ";
        std::string choiceId = inputDecorator.getUserInput();  // 사용자 입력 받기

        // 선택을 EventManager에 전달하여 처리
        EventManager& manager = EventManager::getInstance();
        manager.executeChoice(choiceId, this, player);

        // 만약 유효한 선택이었다면 루프를 종료
        if (std::find_if(choices.begin(), choices.end(), [&](const Choice& choice) {
                return choice.getId() == choiceId;
            }) != choices.end()) {
            break;
        } else {
            // 잘못된 입력 처리 시 선택지를 다시 표시
            std::cout << "Invalid choice ID. Please try again." << std::endl;
            displayChoices();
        }
    }
}


// 몬스터를 설정하는 함수
void Event::setMonster(std::unique_ptr<BaseMonster> monster) {
    this->monster = std::move(monster);
}

bool Event::hasMonster() const { //// 몬스터가 있는지 여부를 확인하는 함수
    return monster != nullptr;
}

BaseMonster* Event::getMonster() const { //// 현재 이벤트의 몬스터를 반환하는 함수
    return monster.get();
}

//NPC설정
void Event::setNPC(std::unique_ptr<BaseNPC> npc) {
    this->npc = std::move(npc);
}

bool Event::hasNPC() const {
    return npc != nullptr;
}

BaseNPC* Event::getNPC() const {
    return npc.get();
}

//트랩설정
void Event::setTrap(std::unique_ptr<BaseTrap> trap) {
    this->trap = std::move(trap);
}

bool Event::hasTrap() const {
    return trap != nullptr;
}

BaseTrap* Event::getTrap() const {
    return trap.get();
}
