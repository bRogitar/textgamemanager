#include "Event.h"
#include <iostream>

Event::Event(const std::string& eventId, const std::string& eventText)
    : eventId(eventId), eventText(eventText), monster(nullptr) {}

Event::Event(const std::string& eventId, const std::string& name, const std::string& description)
    : eventId(eventId), name(name), eventText(description), monster(nullptr) {} // monster 멤버 변수도 초기화

void Event::addChoice(const Choice& choice) {
    choices.push_back(choice);
}

void Event::displayChoices() const {
    for (size_t i = 0; i < choices.size(); ++i) {
        std::cout << i + 1 << ". " << choices[i].getDescription() << std::endl;
    }
}

void Event::executeChoice(int choiceIndex, Player& player) {
    if (choiceIndex >= 0 && choiceIndex < static_cast<int>(choices.size())) {
        choices[choiceIndex].execute(player);
    } else {
        std::cout << "Invalid choice selected!" << std::endl;
    }
}

std::string Event::getEventText() const {
    return eventText;
}

void Event::execute(Player& player) {
    std::cout << getEventText() << "\n";
    displayChoices();

    std::cout << "Enter your choice: ";
    int choiceIndex;
    std::cin >> choiceIndex;

    // 선택지를 1부터 사용자에게 보여주었으므로, 인덱스는 -1을 해주어야 함
    executeChoice(choiceIndex - 1, player);
}

void Event::setMonster(std::unique_ptr<BaseMonster> monster) {
    this->monster = std::move(monster);
}

bool Event::hasMonster() const {
    return monster != nullptr;
}

BaseMonster* Event::getMonster() const {
    return monster.get();
}
