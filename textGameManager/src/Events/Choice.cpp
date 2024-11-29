// Choice.h
#ifndef CHOICE_H
#define CHOICE_H

#include <string>
#include <memory>
#include "BaseAction.h"

class Choice {
private:
    std::string id;
    std::string description;
    std::unique_ptr<BaseAction> action;
    std::string nextEventId; // 후속 이벤트 ID

public:
    Choice(const std::string& id, const std::string& description, std::unique_ptr<BaseAction> action, const std::string& nextEventId = "")
        : id(id), description(description), action(std::move(action)), nextEventId(nextEventId) {}

    const std::string& getId() const {
        return id;
    }

    const std::string& getDescription() const {
        return description;
    }

    const std::string& getNextEventId() const {
        return nextEventId;
    }

    void execute(Player& player) const {
        if (action) {
            action->execute(player);
        }
    }
};

#endif // CHOICE_H
