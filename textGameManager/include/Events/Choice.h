#ifndef CHOICE_H
#define CHOICE_H

#include <string>
#include <memory>
#include "BaseAction.h"
#include "BaseTrap.h"
#include "Player.h"

class Choice {
private:
    std::string id;
    std::string description;
    std::unique_ptr<BaseAction> action;
    std::string nextEventId;
    std::string abilityId;
    std::unique_ptr<BaseTrap> trap;

public:
    Choice(const std::string& id, 
           const std::string& description, 
           std::unique_ptr<BaseAction> action,
           const std::string& nextEventId = "", 
           const std::string& abilityId = "",
           std::unique_ptr<BaseTrap> trap = nullptr)
        : id(id), 
          description(description), 
          action(std::move(action)), 
          nextEventId(nextEventId), 
          abilityId(abilityId),
          trap(std::move(trap)) {}

    // 이동 생성자 추가
    Choice(Choice&& other) noexcept
        : id(std::move(other.id))
        , description(std::move(other.description))
        , action(std::move(other.action))
        , nextEventId(std::move(other.nextEventId))
        , abilityId(std::move(other.abilityId))
        , trap(std::move(other.trap)) {
        //std::cout << "[DEBUG] Choice move constructor - Trap exists: " 
        //          << (trap != nullptr) << std::endl;
    }

    void execute(Player& player) const {
        if (trap) {
            trap->trigger(player);
        }
        
        if (action) {
            action->execute(player);
        }
    }

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

};

#endif // CHOICE_H
