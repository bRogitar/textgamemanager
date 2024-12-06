#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include <memory>
#include "Choice.h"
#include "BaseMonster.h"
#include "BaseTrap.h"
#include "BaseNPC.h"

class Event {
public:
    // 생성자 정의
    Event(const std::string& eventId, const std::string& eventName, const std::string& eventDescription)
        : id(eventId), name(eventName), description(eventDescription), completed(false), hasAbilityRewardFlag(false) {}

    // 선택을 추가하는 함수
    void addChoice(Choice&& choice) {
        choices.push_back(std::move(choice));
    }

    // 선택 목록 반환
    const std::vector<Choice>& getChoices() const {
        return choices;
    }

    // 이벤트 실행 함수
    void execute(Player& player);
    
    // 선택지 화면 표시 함수
    void displayChoices() const;

    // 이벤트 텍스트 반환 함수
    std::string getEventText() const {
        return description;
    }


    // 몬스터 설정 함수
    void setMonster(std::unique_ptr<BaseMonster> monster);

    // 몬스터 여부 확인 함수
    bool hasMonster() const;

    // 현재 이벤트의 몬스터 반환 함수
    BaseMonster* getMonster() const;

    
    void setNPC(std::unique_ptr<BaseNPC> npc);
    bool hasNPC() const;
    BaseNPC* getNPC() const;


    void setTrap(std::unique_ptr<BaseTrap> trap);
    bool hasTrap() const;
    BaseTrap* getTrap() const;


    // 이벤트 완료 상태 관리
    void markAsCompleted() {
        completed = true;
    }

    bool isCompleted() const {
        return completed;
    }

    // 다음 이벤트 ID 설정 및 반환 함수
    void setNextEventId(const std::string& eventId) {
        nextEventId = eventId;
    }

    const std::string& getNextEventId() const {
        return nextEventId;
    }

    // Ability 보상 관련 함수 추가
    void setAbilityReward(const std::string& abilityId) {
        hasAbilityRewardFlag = true;
        abilityRewardId = abilityId;
    }

    // getter 함수는 단순히 값을 반환합니다.
    bool hasAbilityReward() const {
        return hasAbilityRewardFlag;
    }

    std::string getAbilityRewardId() const {
        return abilityRewardId;
    }

private:
    bool completed;                   // 이벤트 완료 여부
    std::string id;                   // 이벤트 ID
    std::string name;                 // 이벤트 이름
    std::string description;          // 이벤트 설명
    std::vector<Choice> choices;      // 선택 목록
    std::unique_ptr<BaseMonster> monster; // 이벤트와 연결된 몬스터
    std::string nextEventId;          // 다음 이벤트 ID
    bool hasAbilityRewardFlag;        // 어빌리티 보상 여부 (변수 이름 변경)
    std::string abilityRewardId;      // 어빌리티 보상 ID
};

#endif // EVENT_H
