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
    std::string nextEventId;  // 후속 이벤트 ID
    std::string abilityId;    // 어빌리티 ID (선택지로 얻을 수 있는 어빌리티)

public:
    // 생성자에 nextEventId와 abilityId 추가
    Choice(const std::string& id, const std::string& description, std::unique_ptr<BaseAction> action, 
           const std::string& nextEventId = "", const std::string& abilityId = "")
        : id(id), description(description), action(std::move(action)), nextEventId(nextEventId), abilityId(abilityId) {}

    // 이동 생성자 추가
    Choice(Choice&& other) noexcept
        : id(std::move(other.id)),
          description(std::move(other.description)),
          action(std::move(other.action)),
          nextEventId(std::move(other.nextEventId)),
          abilityId(std::move(other.abilityId)) {}

    // 이동 할당 연산자 추가
    Choice& operator=(Choice&& other) noexcept {
        if (this != &other) {
            id = std::move(other.id);
            description = std::move(other.description);
            action = std::move(other.action);
            nextEventId = std::move(other.nextEventId);
            abilityId = std::move(other.abilityId);
        }
        return *this;
    }

    // 복사 생성자와 복사 할당 연산자는 삭제하여 이동만 가능하도록 함
    Choice(const Choice& other) = delete;
    Choice& operator=(const Choice& other) = delete;

    // Getter 메서드들
    const std::string& getId() const {
        return id;
    }

    const std::string& getDescription() const {
        return description;
    }

    const std::string& getNextEventId() const {
        return nextEventId;
    }

    // 어빌리티 ID를 반환하는 함수 추가
    const std::string& getAbilityId() const {
        return abilityId;
    }

    // 실행 메서드
    void execute(Player& player) const {
        if (action) {
            action->execute(player);
        }
    }
};

#endif // CHOICE_H
