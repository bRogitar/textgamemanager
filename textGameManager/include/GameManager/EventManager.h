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
    
    // 이벤트를 로드하는 함수 (이벤트 XML 파일을 모두 로드하여 캐싱할 수도 있음)
    void loadEvents(const std::string& filePath);
    
    // 특정 이벤트를 가져오는 함수
    Event* getEvent(const std::string& eventId);
    
    // 특정 이벤트를 처리하는 함수 (플레이어와 이벤트 처리)
    void processEvent(const std::string& eventId, Player& player);
    
    // 플레이어의 선택을 실행하는 함수
    void executeChoice(const std::string& choiceId, Event* currentEvent, Player& player);

private:
    EventManager();
    ~EventManager() = default;
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    // 이벤트 XML로부터 특정 이벤트를 로드하는 함수 (Private)
    std::unique_ptr<Event> loadEventFromXML(const std::string& filePath, const std::string& eventId);

    // 선택지에 따른 효과를 적용하는 함수 (Private)
    void applyChoiceEffects(const Choice& choice, Player& player);

    // 이벤트들을 관리하는 맵 (ID와 이벤트 포인터로 구성)
    std::map<std::string, std::unique_ptr<Event>> events;  // Event 객체를 고유 포인터로 관리
};

#endif // EVENTMANAGER_H