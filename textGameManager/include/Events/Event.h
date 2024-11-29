#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include <memory>
#include "Choice.h"
#include "BaseMonster.h"

class Event {
public:

    void markAsCompleted() {
        completed = true;
    }

    bool isCompleted() const {
        return completed;
    }

    Event(const std::string& eventId, const std::string& eventName, const std::string& eventDescription)
        : id(eventId), name(eventName), description(eventDescription) {}

    void addChoice(Choice&& choice) {
        choices.push_back(std::move(choice));
    }

    // 선택지 리스트 반환
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
    

private:
    std::string id;
    std::string name;
    std::string description;
    std::vector<Choice> choices;
    std::unique_ptr<BaseMonster> monster;
    bool completed = false;
};

#endif // EVENT_H
