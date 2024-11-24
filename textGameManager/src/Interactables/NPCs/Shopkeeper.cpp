#include "Shopkeeper.h"

Shopkeeper::Shopkeeper(const std::string& id, const std::string& name, const std::string& dialogue)
    : BaseNPC(id, name, dialogue) {}

void Shopkeeper::addShopItem(const Item& item, int price) {
    shopInventory.push_back(std::make_pair(item, price));
}

void Shopkeeper::removeShopItem(const std::string& itemId) {
    shopInventory.erase(
        std::remove_if(shopInventory.begin(), shopInventory.end(),
            [&itemId](const auto& pair) { return pair.first.getId() == itemId; }),
        shopInventory.end()
    );
}

bool Shopkeeper::sellItem(Player* player, const std::string& itemId) {
    auto it = std::find_if(shopInventory.begin(), shopInventory.end(),
        [&itemId](const auto& pair) { return pair.first.getId() == itemId; });
    
    if (it != shopInventory.end() && player->getMoney() >= it->second) {
        player->modifyMoney(-it->second);
        player->addItem(it->first);
        return true;
    }
    return false;
}

void Shopkeeper::interact(Player* player) {
    std::cout << "Welcome to " << getName() << "'s shop!" << std::endl;
    std::cout << getDialogue() << std::endl;
    // 상점 인벤토리 표시 및 거래 처리
}
