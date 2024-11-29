#include "Event.h"
#include <iostream>
#include <limits>
#include "CombatManager.h"
#include <algorithm>

// Event Constructor: 기본 이벤트 생성자는 헤더 파일에만 존재

// 선택지를 화면에 표시하는 함수
void Event::displayChoices() const {
    for (const auto& choice : choices) {
        std::cout << choice.getId() << ": " << choice.getDescription() << std::endl;
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

    // 유효한 선택지 ID를 입력받기
    std::string choiceId;
    while (true) {
        std::cout << "Enter your choice ID: ";
        std::cin >> choiceId;

        // 입력값 검증 및 선택 실행
        if (std::any_of(choices.begin(), choices.end(), [&](const Choice& choice) {
                return choice.getId() == choiceId;
            })) {
            executeChoice(choiceId, player);
            break; // 유효한 선택지를 실행하면 루프 종료
        } else {
            std::cout << "Invalid choice ID. Please try again.\n";
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