#include "Event.h"
#include <iostream>
#include <limits>
#include "CombatManager.h"

// Event Constructor: 기본 이벤트 생성자는 헤더 파일에만 존재

// 선택지를 화면에 표시하는 함수
void Event::displayChoices() const {
    for (size_t i = 0; i < choices.size(); ++i) {
        std::cout << i + 1 << ". " << choices[i].getDescription() << " (" << choices[i].getId() << ")" << std::endl;
    }
}

// 선택지를 실행하는 함수 (문자열 ID로 확인)
void Event::executeChoice(const std::string& choiceId, Player& player) {
    for (const auto& choice : choices) {
        if (choice.getId() == choiceId) {
            choice.execute(player); // 선택지에 연결된 행동 실행
            return;
        }
    }
    std::cout << "Invalid choice ID." << std::endl;
}

// 이벤트를 실행하는 함수
void Event::execute(Player& player) {
    std::cout << description << "\n";
    displayChoices();

    std::cout << "Enter your choice: ";
    int choiceIndex;
    std::cin >> choiceIndex;

    // 입력 검증
    while (std::cin.fail() || choiceIndex < 1 || choiceIndex > static_cast<int>(choices.size())) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please enter a valid choice: ";
        std::cin >> choiceIndex;
    }

    // 선택지 실행
    const std::string choiceId = choices[choiceIndex - 1].getId();
    executeChoice(choiceId, player);
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
