#include "Event.h"
#include <iostream>
#include <limits>
#include "CombatManager.h"
#include <algorithm>
#include "EventManager.h"

// Event Constructor: 기본 이벤트 생성자는 헤더 파일에만 존재

// 선택지를 화면에 표시하는 함수
void Event::displayChoices() const {
    for (const auto& choice : choices) {
        std::cout << choice.getId() << ": " << choice.getDescription() << std::endl;
    }
}

// 이벤트를 실행하는 함수
void Event::execute(Player& player) {
    std::cout << description << "\n";
    displayChoices();

    while (true) {
        std::cout << "Enter your choice ID: ";
        std::string choiceId;
        std::cin >> choiceId;

        // 선택 실행을 EventManager에 위임
        EventManager& manager = EventManager::getInstance();
        auto& choices = getChoices();

        auto it = std::find_if(choices.begin(), choices.end(), [&](const Choice& choice) {
            return choice.getId() == choiceId;
        });

        if (it != choices.end()) {
            manager.executeChoice(choiceId, this, player);
            break; // 올바른 입력일 경우 루프 종료
        } else {
            std::cout << "Invalid choice ID. Please try again." << std::endl;
            displayChoices(); // 선택지를 다시 표시
        }
    }
}



// 몬스터를 설정하는 함수
void Event::setMonster(std::unique_ptr<BaseMonster> monster) {
    this->monster = std::move(monster);
}

// 몬스터가 있는지 여부를 확인하는 함수
bool Event::hasMonster() const {
    return monster != nullptr;
}

// 현재 이벤트의 몬스터를 반환하는 함수
BaseMonster* Event::getMonster() const {
    return monster.get();
}