#include "EventManager.h"
#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include "MonsterFactory.h"
#include "FightAction.h"
#include "Event.h"
#include "RunAwayAction.h"
#include <algorithm>
#include "InputManager.h"

using namespace tinyxml2;

EventManager& EventManager::getInstance() {
    static EventManager instance;
    return instance;
}

EventManager::EventManager() {}

Event* EventManager::getEvent(const std::string& eventId) {
    auto it = events.find(eventId);
    if (it != events.end()) {
        return it->second.get();
    }
    return nullptr;
}

void EventManager::processEvent(const std::string& eventId, Player& player) {
    Event* event = getEvent(eventId);
    if (event == nullptr) {
        auto loadedEvent = loadEventFromXML("../resources/events.xml", eventId);
        if (loadedEvent) {
            events[eventId] = std::move(loadedEvent);
            event = events[eventId].get();
        } else {
            std::cout << "이벤트 ID: " << eventId << "를 처리할 수 없습니다." << std::endl;
            return;
        }
    }

    if (event->isCompleted()) {
        std::cout << "이 이벤트는 이미 완료되었습니다.\n";
        return;
    }

    event->execute(player);
    event->markAsCompleted();
}

void EventManager::executeChoice(const std::string& choiceId, Event* currentEvent, Player& player) {
    auto& choices = currentEvent->getChoices();
    std::string userChoice = choiceId;

    while (true) {
        auto it = std::find_if(choices.begin(), choices.end(), [&](const Choice& choice) {
            return choice.getId() == userChoice;
        });

        if (it != choices.end()) {
            it->execute(player);

            std::string nextEventId = it->getNextEventId();
            if (nextEventId == "end") {
                std::cout << "축하합니다! 게임을 완료하셨습니다.\n";
                exit(0);
            } else if (!nextEventId.empty()) {
                processEvent(nextEventId, player);
            }
            break;
        } else {
            std::cout << "잘못된 선택입니다. 다시 시도해주세요." << std::endl;
            currentEvent->displayChoices();
            userChoice = InputManager::getInstance().getUserInput();
        }
    }
}

std::unique_ptr<Event> EventManager::loadEventFromXML(const std::string& filePath, const std::string& eventId) {
    XMLDocument doc;
    XMLError eResult = doc.LoadFile(filePath.c_str());
    if (eResult != XML_SUCCESS) {
        std::cerr << "이벤트 파일을 불러오는데 실패했습니다: " << filePath << " 오류 코드: " << eResult << std::endl;
        return nullptr;
    }

    XMLElement* pEventsRoot = doc.FirstChildElement("Events");
    if (pEventsRoot == nullptr) {
        std::cerr << "XML 파일에서 <Events> 루트 요소를 찾을 수 없습니다." << std::endl;
        return nullptr;
    }

    XMLElement* pEventElement = pEventsRoot->FirstChildElement("Event");
    while (pEventElement != nullptr) {
        if (std::string(pEventElement->Attribute("id")) == eventId) {
            std::string name = pEventElement->FirstChildElement("name")->GetText();
            std::string description = pEventElement->FirstChildElement("description")->GetText();

            auto newEvent = std::make_unique<Event>(eventId, name, description);

            BaseMonster* monster = nullptr;
            XMLElement* pMonsterElement = pEventElement->FirstChildElement("Monster");
            if (pMonsterElement != nullptr) {
                std::string monsterName = pMonsterElement->Attribute("name") ? pMonsterElement->Attribute("name") : "알 수 없음";
                int health = 0, attackPower = 0;
                pMonsterElement->QueryIntAttribute("health", &health);
                pMonsterElement->QueryIntAttribute("attackPower", &attackPower);

                monster = MonsterFactory::createMonster(monsterName, health, attackPower).release();
                newEvent->setMonster(std::unique_ptr<BaseMonster>(monster));
            }

            XMLElement* pChoices = pEventElement->FirstChildElement("Choices");
            if (pChoices != nullptr) {
                for (XMLElement* pChoice = pChoices->FirstChildElement("Choice");
                     pChoice != nullptr;
                     pChoice = pChoice->NextSiblingElement("Choice")) {

                    std::string choiceId = pChoice->Attribute("id");
                    std::string choiceDescription = pChoice->Attribute("description");
                    std::string nextEventId = pChoice->Attribute("nextEventId");

                    std::unique_ptr<BaseAction> action;

                    if (choiceId == "fight") {
                        action = std::make_unique<FightAction>(monster);
                    } else if (choiceId == "run") {
                        action = std::make_unique<RunAwayAction>();
                    } else {
                        action = std::make_unique<FightAction>();
                    }

                    Choice choice(choiceId, choiceDescription, std::move(action), nextEventId);
                    newEvent->addChoice(std::move(choice));
                }
            }
            return newEvent;
        }
        pEventElement = pEventElement->NextSiblingElement("Event");
    }

    std::cerr << "ID가 " << eventId << "인 이벤트를 찾을 수 없습니다." << std::endl;
    return nullptr;
}