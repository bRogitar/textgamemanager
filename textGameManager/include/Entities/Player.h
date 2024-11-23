// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "AbilityInventory.h"
#include "ItemInventory.h"
#include "PlayerStatus.h"

class Player {
public:
    Player();
    Player(const std::string& name, int strength, int health);
    void modifyHealth(int amount);
    void addItem(const Item& item);
    void removeItem(const Item& item);
    bool hasItem(const std::string& itemId) const;
    void addAbility(const Ability& ability);
    void removeAbility(const Ability& ability);
    bool hasAbility(const std::string& abilityId) const;

    std::string name;
    PlayerStatus status;
    ItemInventory itemInventory;
    AbilityInventory abilityInventory;
};

#endif // PLAYER_H