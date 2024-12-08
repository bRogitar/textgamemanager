#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <string>
#include <map>
#include <memory>
#include "Event.h"
#include "Player.h"
#include "tinyxml2.h"

class EventManager {
public:
    static EventManager& getInstance();
    
    // 이벤트를 로드 (이벤트 XML 파일을 모두 로드하여 캐싱 가능)
    void loadEvents(const std::string& filePath);
    
    // 특정 이벤트를 가져오기
    Event* getEvent(const std::string& eventId);
    
    // 특정 이벤트를 처리 (플레이어와 이벤트 처리)
    std::string processEvent(const std::string& eventId, Player& player);
    
    // 플레이어의 선택을 실행
    void executeChoice(const std::string& choiceId, Event* currentEvent, Player& player);

private:
    EventManager();
    ~EventManager() = default;
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    // 이벤트 XML로부터 특정 이벤트를 로드
    std::unique_ptr<Event> loadEventFromXML(const std::string& filePath, const std::string& eventId);

    // 선택지에 따른 효과를 적용
    void applyChoiceEffects(const Choice& choice, Player& player);

    // 이벤트들을 관리 맵 (ID와 이벤트 포인터로 구성)
    std::map<std::string, std::unique_ptr<Event>> events;  // Event 객체를 고유 포인터 관리하기
};

#endif // EVENTMANAGER_H