#include "EventManager.h"
#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include "MonsterFactory.h"
#include "FightAction.h"  // ConcreteAction 클래스 포함
#include "Event.h"
#include "RunAwayAction.h"
#include "GetPotionAction.h"
#include "ContinueAction.h"
#include <algorithm>
#include "GameManager.h"
#include "InputDecorator.h"
#include "InputManager.h"
#include <cctype> // tolower 함수 포함

using namespace tinyxml2;

EventManager& EventManager::getInstance() {
    static EventManager instance;
    return instance;
}

EventManager::EventManager() {}

Event* EventManager::getEvent(const std::string& eventId) {
    auto it = events.find(eventId);
    if (it != events.end()) {
        return it->second.get(); // unique_ptr에서 원시 포인터로 변환
    }
    return nullptr;
}

void EventManager::processEvent(const std::string& eventId, Player& player) {
    std::cout << "[DEBUG] Processing event with ID: " << eventId << std::endl;

    Event* event = getEvent(eventId);
    if (event == nullptr) {
        auto loadedEvent = loadEventFromXML("../resources/events.xml", eventId);
        if (loadedEvent) {
            events[eventId] = std::move(loadedEvent);
            event = events[eventId].get();
            std::cout << "[DEBUG] Loaded new event with ID: " << eventId << std::endl;
        } else {
            std::cout << "Unable to process event with ID: " << eventId << std::endl;
            return;
        }
    }

    // 이벤트 실행
    std::cout << "[DEBUG] Executing event: " << eventId << std::endl;
    event->execute(player);
    event->markAsCompleted();
}

void EventManager::executeChoice(const std::string& choiceId, Event* currentEvent, Player& player) {
    auto& choices = currentEvent->getChoices();

    // 입력된 선택지에 대해 검사
    auto it = std::find_if(choices.begin(), choices.end(), [&](const Choice& choice) {
        return choice.getId() == choiceId;
    });

    if (it != choices.end()) {
        // 유효한 선택지를 실행
        it->execute(player);

        // 다음 이벤트로 이동할지 결정
        std::string nextEventId = it->getNextEventId();
        if (nextEventId == "end") {
            // "end"로 끝나는 이벤트는 종료 메시지를 표시하고 제어를 반환
            std::cout << "Event chain ended. Proceeding to next room...\n";
            return;
        } else if (!nextEventId.empty()) {
            // 다음 이벤트 ID가 있으면 이를 설정하고, 다음번에 GameManager가 호출할 수 있도록 합니다.
            currentEvent->setNextEventId(nextEventId);
        }
    } else {
        // 잘못된 입력 처리
        std::cout << "Invalid choice ID.\n";
    }
}

std::unique_ptr<Event> EventManager::loadEventFromXML(const std::string& filePath, const std::string& eventId) {
    XMLDocument doc;
    XMLError eResult = doc.LoadFile(filePath.c_str());
    if (eResult != XML_SUCCESS) {
        std::cerr << "Failed to load events from " << filePath << " Error code: " << eResult << std::endl;
        return nullptr;
    }

    XMLElement* pEventsRoot = doc.FirstChildElement("Events");
    if (pEventsRoot == nullptr) {
        std::cerr << "No root element <Events> found in XML file." << std::endl;
        return nullptr;
    }

    XMLElement* pEventElement = pEventsRoot->FirstChildElement("Event");
    while (pEventElement != nullptr) {
        if (std::string(pEventElement->Attribute("id")) == eventId) {
            std::string name = pEventElement->FirstChildElement("name")->GetText();
            std::string description = pEventElement->FirstChildElement("description")->GetText();

            auto newEvent = std::make_unique<Event>(eventId, name, description);

            // 몬스터 정보를 읽어들임
            XMLElement* pMonsterElement = pEventElement->FirstChildElement("Monster");
            BaseMonster* monster = nullptr;
            if (pMonsterElement != nullptr) {
                std::string monsterType = pMonsterElement->Attribute("type") ? pMonsterElement->Attribute("type") : "Unknown";
                std::string monsterName = pMonsterElement->Attribute("name") ? pMonsterElement->Attribute("name") : "Unknown";
                int health = 0, attackPower = 0;
                pMonsterElement->QueryIntAttribute("health", &health);
                pMonsterElement->QueryIntAttribute("attackPower", &attackPower);

                // 몬스터 객체 생성
                auto createdMonster = MonsterFactory::createMonster(monsterType, monsterName, health, attackPower);
                if (createdMonster) {
                    monster = createdMonster.get(); // 포인터로 저장 후 이벤트에 추가
                    newEvent->setMonster(std::move(createdMonster));
                } else {
                    std::cerr << "Failed to create monster of type: " << monsterType << std::endl;
                }
            }

            // Choices 정보를 읽어들임
            XMLElement* pChoices = pEventElement->FirstChildElement("Choices");
            if (pChoices != nullptr) {
                for (XMLElement* pChoice = pChoices->FirstChildElement("Choice"); pChoice != nullptr; pChoice = pChoice->NextSiblingElement("Choice")) {
                    std::string choiceId = pChoice->Attribute("id");
                    std::string choiceDescription = pChoice->Attribute("description");
                    std::string nextEventId = pChoice->Attribute("nextEventId");

                    std::unique_ptr<BaseAction> action;

    if (choiceId == "fight") {
        // 전투 액션에 생성된 몬스터 전달
        if (monster) {
            action = std::make_unique<FightAction>(monster);
        } else {
            // 몬스터가 없으면 전투 선택지를 건너뜁니다.
            continue;
            }
        } else if (choiceId == "run") {
            action = std::make_unique<RunAwayAction>();
        } else if (choiceId == "get potion") {
            action = std::make_unique<GetPotionAction>(); // 포션을 획득하는 행동
        } else if (choiceId == "continue") {
            action = std::make_unique<ContinueAction>(); // 포션을 획득하는 행동
        } else {
            action = nullptr;
        }
    Choice choice(choiceId, choiceDescription, std::move(action), nextEventId);
    newEvent->addChoice(std::move(choice));
                }
            }
            return newEvent;
        }
        pEventElement = pEventElement->NextSiblingElement("Event");
    }

    std::cerr << "Event with ID " << eventId << " not found." << std::endl;
    return nullptr;
}


