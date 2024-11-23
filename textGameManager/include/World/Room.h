// Room.h
#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "IInteractable.h"

class Room {
public:
    Room(const std::string& roomId, const std::string& roomName, const std::string& description);
    void enter();
    void displayDescription() const;
    IInteractable* getInteractable(const std::string& interactableId);
    std::string getRoomId() const;
    bool isCleared() const;
    void setCleared(bool cleared);
    std::string getRoomName() const; // Added getter for roomName
    bool hasEvent() const;
    void setHasEvent(bool hasEvent);


private:
    std::string roomId;
    std::string roomName;
    std::string roomDescription;
    std::vector<IInteractable*> interactables;
    bool cleared;
    bool event; // Add `event` member to `Room` class
    };

#endif // ROOM_H