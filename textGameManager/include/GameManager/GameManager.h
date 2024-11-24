#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>
#include <vector>
#include "tinyxml2.h"
#include "Room.h"
#include "Player.h"
#include "MonsterFactory.h"

using namespace tinyxml2;

class GameManager {
public:
    static GameManager& getInstance();
    void initializeGame();
    void startGame();
    void gameLoop();
    void displayOptions(const std::vector<std::string>& options);
    std::string getUserInput();
    void startCombat(BaseMonster enemy);
    void saveGame(const std::string& filename);
    void loadGame(const std::string& filename);
    Event loadEvent(const std::string& eventId);
    void displayMessage(const std::string& message);
    std::vector<std::string> getSaveFiles() const;
    bool confirmAction(const std::string& message);

private:
    GameManager(); // Private constructor for singleton
    ~GameManager() = default;
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

    // Save/Load methods
    void savePlayerData(XMLDocument& doc, const Player& player);
    void loadPlayerData(const XMLElement* playerElement, Player& player);
    const std::string SAVE_DIRECTORY = "saves/";

    // Input methods
    bool validateInput(const std::string& input, int optionsCount) const;
    void displayPrompt() const;

    Player player;
    std::vector<Room> worldMap;
    std::vector<Room> createWorldMap();
};

#endif // GAMEMANAGER_H
