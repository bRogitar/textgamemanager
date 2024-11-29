#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include <memory>  // 추가됨
#include "Choice.h"
#include "BaseMonster.h"

class Event {
public:
    Event(const std::string& eventId, const std::string& eventText);
    Event(const std::string& eventId, const std::string& name, const std::string& description);

    void addChoice(const Choice& choice);
    void displayChoices() const;
    void executeChoice(const std::string& choiceIndex, Player& Player);
    std::string getEventText() const;
    void setMonster(std::unique_ptr<BaseMonster> monster);
    bool hasMonster() const;
    BaseMonster* getMonster() const;
    void execute(Player& player);

private:
    std::string eventId;
    std::string eventText;
    std::string name;
    std::vector<Choice> choices;
    std::unique_ptr<BaseMonster> monster;  // Monster와 관련된 유일한 소유권을 위해 unique_ptr 사용
};

#endif // EVENT_H
