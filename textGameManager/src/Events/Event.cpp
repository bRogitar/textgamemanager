#include "Event.h"
#include <iostream>
#include <limits>
#include "CombatManager.h"

// Event Constructor: 기본 이벤트 생성자
Event::Event(const std::string& eventId, const std::string& eventText)
    : eventId(eventId), eventText(eventText), monster(nullptr) {}

// Event Constructor: 이름과 설명이 있는 이벤트 생성자
Event::Event(const std::string& eventId, const std::string& name, const std::string& description)
    : eventId(eventId), name(name), eventText(description), monster(nullptr) {}

// 선택지를 추가하는 함수
void Event::addChoice(const Choice& choice) {
    choices.push_back(choice);
}

// 선택지를 화면에 표시하는 함수
void Event::displayChoices() const {
    for (size_t i = 0; i < choices.size(); ++i) {
        std::cout << i + 1 << ". " << choices[i].getDescription() << std::endl;
    }
}

// 선택지를 실행하는 함수
void Event::executeChoice(int choiceIndex, Player& player) {
    const Choice& choice = choices[choiceIndex];

    // 전투 선택지인지 확인
    if (choice.getId() == "fight") {
        if (monster != nullptr) {
            CombatManager combatManager(player, monster.get()); // 포인터 전달
            combatManager.startCombat();
        } else {
            std::cout << "No monster assigned to this event for combat!" << std::endl;
        }
    } else {
        choice.execute(player); // 일반 선택지 실행
    }
}

// 이벤트를 실행하는 함수
void Event::execute(Player& player) {
    std::cout << getEventText() << "\n";
    displayChoices();

    std::cout << "Enter your choice: ";
    int choiceIndex;
    std::cin >> choiceIndex;

    // 입력 검증
    while (std::cin.fail() || choiceIndex < 1 || choiceIndex > static_cast<int>(choices.size())) {
        std::cin.clear(); // 입력 상태 플래그를 재설정합니다.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 잘못된 입력을 제거합니다.
        std::cout << "Invalid choice. Please enter a valid choice: ";
        std::cin >> choiceIndex;
    }

    // 선택지를 1부터 사용자에게 보여주었으므로, 인덱스는 -1을 해주어야 함
    executeChoice(choiceIndex - 1, player);
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
