#ifndef ROOM_H
#define ROOM_H

#include <string>

class Room {
public:
    Room(const std::string& id, const std::string& name, const std::string& description, const std::string& eventId = "");

    void enter();
    void displayDescription() const;
    bool isCleared() const;
    void setCleared(bool cleared);
    bool hasEvent() const;
    std::string getRoomId() const;
    std::string getRoomName() const;
    std::string getEventId() const;

private:
    std::string roomId;
    std::string roomName;
    std::string roomDescription;
    std::string eventId;
    bool cleared;
};

#endif // ROOM_H
