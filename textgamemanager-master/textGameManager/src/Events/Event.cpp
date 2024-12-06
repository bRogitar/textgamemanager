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

        // NPC 대화 표시
    if (hasNPC()) {
        std::cout << npc->getName() << ": " << npc->getDialog() << "\n\n";
    }
    
    displayChoices();

    InputManager* inputManager = InputManager::getInstance();
    InputDecorator inputDecorator(inputManager);

    while (true) {
        std::cout << "Enter your choice ID: ";
        std::string choiceId = inputDecorator.getUserInput();
        
        // 입력을 소문자로 변환
        std::transform(choiceId.begin(), choiceId.end(), choiceId.begin(), ::tolower);

        auto it = std::find_if(choices.begin(), choices.end(),
            [&](const Choice& choice) { 
                std::string fullId = choice.getId();
                std::transform(fullId.begin(), fullId.end(), fullId.begin(), ::tolower);
                // 전체 ID나 첫 글자 매칭 모두 허용
                return fullId == choiceId || (choiceId.length() == 1 && fullId[0] == choiceId[0]);
            });

        if (it != choices.end()) {
            it->execute(player);
            nextEventId = it->getNextEventId();
            break;
        } else {
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
