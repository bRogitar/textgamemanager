#include "EventManager.h"
#include "tinyxml2.h"
#include <iostream>
#include <fstream>

using namespace tinyxml2;

EventManager& EventManager::getInstance() {
    static EventManager instance;
    return instance;
}

EventManager::EventManager() {}

Event* EventManager::getEvent(const std::string& eventId) {
    auto it = events.find(eventId);
    if (it != events.end()) {
        return it->second;
    }
    return nullptr;
}

void EventManager::processEvent(const std::string& eventId, Player& player) {
    Event* event = getEvent(eventId);
    if (event != nullptr) {
        event->execute(player);
    } else {
        std::cout << "Event with ID " << eventId << " not found." << std::endl;
    }
}

void EventManager::executeChoice(const std::string& choiceId, Event* currentEvent, Player& player) {
    if (currentEvent != nullptr) {
        currentEvent->executeChoice(choiceId, player);
    } else {
        std::cout << "No current event to execute choice for." << std::endl;
    }
}