#include "EventManager.h"
#include "tinyxml2.h"
#include <iostream>
#include <fstream>
#include "MonsterFactory.h"
#include "FightAction.h"  // ConcreteAction 클래스 포함
#include "Event.h"
#include "RunAwayAction.h"
#include <algorithm>
#include "GameManager.h"

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
    Event* event = getEvent(eventId);
    if (event == nullptr) {
        auto loadedEvent = loadEventFromXML("../resources/events.xml", eventId);
        if (loadedEvent) {
            events[eventId] = std::move(loadedEvent);
            event = events[eventId].get();
        } else {
            std::cout << "Unable to process event with ID: " << eventId << std::endl;
            return;
        }
    }

    // 이벤트 완료 상태 확인
    if (event->isCompleted()) {
        std::cout << "This event has already been completed.\n";
        return;
    }

    // 이벤트 실행
    event->execute(player);
    event->markAsCompleted();
}

void EventManager::executeChoice(const std::string& choiceId, Event* currentEvent, Player& player) {
    auto& choices = currentEvent->getChoices();
    std::string userChoice = choiceId; // 초기 선택값

    while (true) { // 루프 유지
        auto it = std::find_if(choices.begin(), choices.end(), [&](const Choice& choice) {
            return choice.getId() == userChoice;
        });

        if (it != choices.end()) {
            // 유효한 선택지를 실행
            it->execute(player);

            // 다음 이벤트로 이동
            std::string nextEventId = it->getNextEventId();
            if (nextEventId == "end") {
                std::cout << "Congratulations! You have completed the game.\n";
                exit(0); // 프로그램 종료
            } else if (!nextEventId.empty()) {
                processEvent(nextEventId, player);
            }
            break; // 올바른 입력이므로 루프 종료
        } else {
            // 잘못된 입력 처리
            std::cout << "Invalid choice ID. Please try again." << std::endl;

            // 선택지를 다시 표시
            currentEvent->displayChoices();

            // 새 입력을 받음
            userChoice = GameManager::getInstance().getUserInput();
        }
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
                for (XMLElement* pChoice = pChoices->FirstChildElement("Choice");
                     pChoice != nullptr;
                     pChoice = pChoice->NextSiblingElement("Choice")) {

                    std::string choiceId = pChoice->Attribute("id");
                    std::string choiceDescription = pChoice->Attribute("description");
                    std::string nextEventId = pChoice->Attribute("nextEventId");

                    std::unique_ptr<BaseAction> action;

                    if (choiceId == "fight") {
                        // 전투 액션에 생성된 몬스터 전달
                        if (monster) {
                            action = std::make_unique<FightAction>(monster);
                        } else {
                            std::cerr << "No monster found for fight action in event: " << eventId << std::endl;
                            continue;
                        }
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

    std::cerr << "Event with ID " << eventId << " not found." << std::endl;
    return nullptr;
}
