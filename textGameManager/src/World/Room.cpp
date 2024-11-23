// Room.cpp
#include "Room.h"
#include <iostream>

Room::Room(const std::string& roomId, const std::string& roomName, const std::string& description)
    : roomId(roomId), roomName(roomName), roomDescription(description), cleared(false) {}

void Room::enter() {
    std::cout << "You have entered " << roomName << ".\n";
    displayDescription();
}

void Room::displayDescription() const {
    std::cout << roomDescription << "\n";
}

IInteractable* Room::getInteractable(const std::string& interactableId) {
    for (auto& interactable : interactables) {
        if (interactable->getInteractableId() == interactableId) {
            return interactable;
        }
    }
    return nullptr;
}

std::string Room::getRoomId() const {
    return roomId;
}

bool Room::isCleared() const {
    return cleared;
}

void Room::setCleared(bool cleared) {
    this->cleared = cleared;
}

std::string Room::getRoomName() const {
    return roomName;
}

bool Room::hasEvent() const {
    return event;
}

void Room::setHasEvent(bool hasEvent) {
    event = hasEvent;
}