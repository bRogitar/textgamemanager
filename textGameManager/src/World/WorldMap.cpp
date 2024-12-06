// WorldMap.cpp
#include "WorldMap.h"

void WorldMap::addRoom(const Room& room) {
    rooms[room.getRoomId()] = room;
}

Room* WorldMap::getRoom(const std::string& roomId) {
    auto it = rooms.find(roomId);
    if (it != rooms.end()) {
        return &it->second;
    }
    return nullptr;
}

std::vector<Room*> WorldMap::getAdjacentRooms(const std::string& roomId) {
    // Placeholder logic for returning adjacent rooms
    // In a real implementation, you would have additional data to determine adjacency
    std::vector<Room*> adjacentRooms;
    for (auto& roomPair : rooms) {
        if (roomPair.first != roomId) {
            adjacentRooms.push_back(&roomPair.second);
        }
    }
    return adjacentRooms;
}

std::vector<Room*> WorldMap::getAllRooms() {
    std::vector<Room*> roomsList;
    for (auto& roomPair : rooms) {
        roomsList.push_back(&roomPair.second);
    }
    return roomsList;
}

// 새로 커밋을 합니다. 