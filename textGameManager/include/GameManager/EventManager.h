#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <string>
#include <map>
#include "Event.h"
#include "Player.h"
#include "tinyxml2.h"

class EventManager {
public:
    static EventManager& getInstance();
    void loadEvents();
    Event* getEvent(const std::string& eventId);
    void processEvent(const std::string& eventId, Player& player);
    void executeChoice(const std::string& choiceId, Event* currentEvent, Player& player);

private:
    EventManager();
    ~EventManager() = default;
    EventManager(const EventManager&) = delete;
    EventManager& operator=(const EventManager&) = delete;

    std::map<std::string, Event*> events;
    Event* loadEventFromXML(const int eventId);
    void applyChoiceEffects(const Choice& choice, Player& player);
};

#endif // EVENTMANAGER_H