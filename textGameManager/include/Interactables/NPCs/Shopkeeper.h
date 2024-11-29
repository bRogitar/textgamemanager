#ifndef SHOPKEEPER_H
#define SHOPKEEPER_H

#include "BaseNPC.h"
#include "../../Entities/Item.h"
#include <vector>
#include <utility>

class Shopkeeper : public BaseNPC {
public:
    Shopkeeper(const std::string& id, const std::string& name, const std::string& dialogue);

    // Shop inventory management
    void addShopItem(const Item& item, int price);
    void removeShopItem(const std::string& itemId);
    bool hasItem(const std::string& itemId) const;
    
    // Trading methods
    bool sellItem(Player* player, const std::string& itemId);
    bool buyItem(Player* player, const std::string& itemId);
    
    // Override interaction method
    void interact(Player* player) override;
    bool canInteract(const Player* player) const override;

    // Getter methods
    std::vector<std::pair<Item, int>> getShopInventory() const;
    int getItemPrice(const std::string& itemId) const;

private:
    std::vector<std::pair<Item, int>> shopInventory; // Item과 가격 쌍
    int minRequiredMoney;
};

#endif // SHOPKEEPER_H