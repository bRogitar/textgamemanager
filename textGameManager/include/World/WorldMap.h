// WorldMap.h
#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Room.h"

class WorldMap {    
public:
    void addRoom(const Room& room);
    Room* getRoom(const std::string& roomId);
    std::vector<Room*> getAdjacentRooms(const std::string& roomId);
    std::vector<Room*> getAllRooms(); //모든 방 포인터 반환

private:
    std::unordered_map<std::string, Room> rooms; 
};

#endif // WORLDMAP_H