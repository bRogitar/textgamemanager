#ifndef SAVELOADMANAGER_H
#define SAVELOADMANAGER_H

#include <string>
#include "Player.h"
#include "tinyxml2.h"

class SaveLoadManager {
public:
    static SaveLoadManager& getInstance();
    bool saveGame(const Player& player, const std::string& filename);
    bool loadGame(Player& player, const std::string& filename);
    std::vector<std::string> getSaveFiles() const;

private:
    SaveLoadManager();
    ~SaveLoadManager() = default;
    SaveLoadManager(const SaveLoadManager&) = delete;
    SaveLoadManager& operator=(const SaveLoadManager&) = delete;

    void savePlayerData(tinyxml2::XMLDocument& doc, const Player& player);
    void loadPlayerData(const tinyxml2::XMLElement* playerElement, Player& player);
    const std::string SAVE_DIRECTORY = "saves/";
};

#endif // SAVELOADMANAGER_H