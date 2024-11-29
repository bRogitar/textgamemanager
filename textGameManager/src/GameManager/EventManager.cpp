// #include "EventManager.h"
// #include "tinyxml2.h"
// #include <iostream>
// #include <fstream>

// using namespace tinyxml2;

// EventManager& EventManager::getInstance() {
//     static EventManager instance;
//     return instance;
// }

// EventManager::EventManager() {}

// void EventManager::loadEvents(const std::string& filePath) {
//     // Load all events from XML file
//     XMLDocument doc;
//     XMLError eResult = doc.LoadFile(filePath.c_str());
//     if (eResult != XML_SUCCESS) {
//         std::cout << "Failed to load events from " << filePath << std::endl;
//         return;
//     }

//     XMLElement* root = doc.FirstChildElement("Events");
//     if (root == nullptr) {
//         std::cout << "Invalid XML format in events file." << std::endl;
//         return;
//     }

//     for (XMLElement* eventElement = root->FirstChildElement("Event"); eventElement != nullptr; eventElement = eventElement->NextSiblingElement("Event")) {
//         std::string eventId = eventElement->Attribute("id") ? eventElement->Attribute("id") : "Unknown";
//         std::string eventDescription = eventElement->FirstChildElement("Description")->GetText() ? eventElement->FirstChildElement("Description")->GetText() : "";

//         Event newEvent(eventId, eventDescription);
//         events[eventId] = newEvent;
//     }

//     std::cout << "Events loaded successfully from " << filePath << std::endl;
// }

// Event* EventManager::getEvent(const std::string& eventId) {
//     auto it = events.find(eventId);
//     if (it != events.end()) {
//         return &it->second;
//     }
//     return nullptr;
// }

// void EventManager::processEvent(const std::string& eventId, Player& player) {
//     Event* event = getEvent(eventId);
//     if (event != nullptr) {
//         event->execute(player);
//     } else {
//         std::cout << "Event with ID " << eventId << " not found." << std::endl;
//     }
// }

// void EventManager::executeChoice(const std::string& choiceId, Event* currentEvent, Player& player) {
//     if (currentEvent != nullptr) {
//         currentEvent->executeChoice(choiceId, player);
//     } else {
//         std::cout << "No current event to execute choice for." << std::endl;
//     }
// }