#ifndef CHOICE_H
#define CHOICE_H

#include <string>
#include <memory>
#include "BaseAction.h"
#include "Player.h"

class Choice {
private:
    std::string id;
    std::string description;
    std::unique_ptr<BaseAction> action;
    std::string nextEventId; // 후속 이벤트 ID

public:
    // 생성자에 nextEventId를 추가
    Choice(const std::string& id, const std::string& description, std::unique_ptr<BaseAction> action, const std::string& nextEventId = "")
        : id(id), description(description), action(std::move(action)), nextEventId(nextEventId) {}

    Choice(const Choice& other) = delete; // 복사 생성자 삭제
    Choice& operator=(const Choice& other) = delete; // 복사 할당 연산자 삭제
    Choice(Choice&& other) noexcept = default; // 이동 생성자
    Choice& operator=(Choice&& other) noexcept = default; // 이동 할당 연산자

    const std::string& getId() const {
        return id;
    }

    const std::string& getDescription() const {
        return description;
    }

    // 후속 이벤트 ID를 반환하는 함수
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