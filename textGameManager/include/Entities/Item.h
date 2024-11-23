// Item.h
#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <unordered_map>

class PlayerStatus; // Forward declaration

class Item {
public:
    Item(const std::string& itemId, const std::string& name, const std::string& description, bool isConsumable);
    void addEffect(const std::string& stat, int value);
    void use(PlayerStatus& playerStatus) const;
    std::string getItemId() const;
    std::string getName() const;
    std::string getDescription() const;

private:
    std::string itemId;
    std::string name;
    std::string description;
    bool isConsumable;
    std::unordered_map<std::string, int> effects;

    friend class ItemInventory;
};

#endif // ITEM_H