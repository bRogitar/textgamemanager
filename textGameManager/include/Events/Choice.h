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

//     핵심 문제는 Choice 클래스의 이동 생성자(move constructor)가 없었던 것이었습니다.
// 문제가 발생한 과정:
// EventManager에서 Choice 객체를 생성할 때 트랩을 포함해서 만들었고
// 이 Choice 객체를 Event의 vector<Choice> choices에 push_back할 때
// 이동 생성자가 없어서 unique_ptr<BaseTrap> trap이 제대로 이동되지 않았습니다
// 해결책은 간단했습니다:
// 이렇게 하면:
// vector에 Choice가 추가될 때 트랩 포인터가 제대로 이동되고
// 나중에 선택지를 실행할 때 트랩이 정상적으로 작동하게 됩니다
// 결국 unique_ptr의 이동 생성자를 추가해주면 해결되는 문제였습니다.

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
