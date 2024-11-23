#include "Room.h"
#include <iostream>

Room::Room(const std::string& id, const std::string& name, const std::string& description, const std::string& eventId)
    : roomId(id), roomName(name), roomDescription(description), eventId(eventId), cleared(false) {}

void Room::enter() {
    std::cout << "You have entered " << roomName << ".\n";
    displayDescription();
}

void Room::displayDescription() const {
    std::cout << roomDescription << "\n";
}

bool Room::isCleared() const {
    return cleared;
}

void Room::setCleared(bool cleared) {
    this->cleared = cleared;
}

bool Room::hasEvent() const {
    return !eventId.empty();
}

std::string Room::getRoomId() const {
    return roomId;
}

std::string Room::getRoomName() const {
    return roomName;
}

std::string Room::getEventId() const {
    return eventId;
}
