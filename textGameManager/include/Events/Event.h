#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include <memory>
#include "Choice.h"
#include "BaseMonster.h"

class Event {
public:
    Event(const std::string& eventId, const std::string& eventName, const std::string& eventDescription)
        : id(eventId), name(eventName), description(eventDescription), completed(false) {}

    void addChoice(Choice&& choice) {
        choices.push_back(std::move(choice));
    }

    const std::vector<Choice>& getChoices() const {
        return choices;
    }

    void execute(Player& player);
    void displayChoices() const;
    void executeChoice(const std::string& choiceIndex, Player& player);
    std::string getEventText() const;
    void setMonster(std::unique_ptr<BaseMonster> monster);
    bool hasMonster() const;
    BaseMonster* getMonster() const;

    // 이벤트 완료 상태 관리
    void markAsCompleted() {
        completed = true;
    }

    bool isCompleted() const {
        return completed;
    }

private:
    std::string id;
    std::string name;
    std::string description;
    std::vector<Choice> choices;
    std::unique_ptr<BaseMonster> monster;
    bool completed; // 이벤트 완료 여부
};

#endif // EVENT_H
