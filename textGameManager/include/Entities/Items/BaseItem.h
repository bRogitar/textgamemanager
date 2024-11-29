// baseitem.h
#ifndef BASEITEM_H
#define BASEITEM_H

#include <string>
#include <unordered_map>

class Player; // Forward declaration

class Item {
public:
    Item(const std::string& itemId, const std::string& name, const std::string& description, bool isConsumable);
    void addEffect(const std::string& stat, int value);
    void use(Player& player) const;
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

#endif // baseitem 