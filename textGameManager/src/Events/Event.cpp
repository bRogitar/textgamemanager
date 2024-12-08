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
    std::cout << "\n===========================\n";
    std::cout << description << "\n";
    std::cout << "===========================\n\n";

    displayChoices();
    
    std::string choiceId = InputManager::getInstance()->getChoiceInput(choices);
    auto it = std::find_if(choices.begin(), choices.end(),
        [&](const Choice& choice) { 
            return choice.getId() == choiceId;
        });
        
    it->execute(player);
    nextEventId = it->getNextEventId();
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
