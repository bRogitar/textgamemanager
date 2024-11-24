#include "Shopkeeper.h"

// Shopkeeper 생성자: ID, 이름, 대사를 설정하고, BaseNPC 생성자를 호출
Shopkeeper::Shopkeeper(const std::string& id, const std::string& name, const std::string& dialogue)
    : BaseNPC(id, name, dialogue) {}

// 상점에 아이템을 추가하는 메서드 (아이템과 가격을 쌍으로 저장)
void Shopkeeper::addShopItem(const Item& item, int price) {
    shopInventory.push_back(std::make_pair(item, price));
}

// 상점에서 특정 ID의 아이템을 제거하는 메서드
void Shopkeeper::removeShopItem(const std::string& itemId) {
    shopInventory.erase(
        std::remove_if(shopInventory.begin(), shopInventory.end(),
            [&itemId](const auto& pair) { return pair.first.getId() == itemId; }), // itemId가 일치하는 아이템 찾기
        shopInventory.end() // 제거된 아이템 이후의 요소를 인벤토리 끝까지 제거
    );
}

// 플레이어에게 특정 아이템을 판매하는 메서드 (성공 시 true 반환, 실패 시 false 반환)
bool Shopkeeper::sellItem(Player* player, const std::string& itemId) {
    // 아이템 ID에 해당하는 아이템을 상점 인벤토리에서 찾기
    auto it = std::find_if(shopInventory.begin(), shopInventory.end(),
        [&itemId](const auto& pair) { return pair.first.getId() == itemId; });
    
    // 아이템이 상점에 있고, 플레이어가 충분한 돈을 가지고 있는 경우
    if (it != shopInventory.end() && player->getMoney() >= it->second) {
        player->modifyMoney(-it->second); // 플레이어의 돈 차감
        player->addItem(it->first); // 플레이어 인벤토리에 아이템 추가
        return true; // 판매 성공
    }
    return false; // 판매 실패
}

// Shopkeeper와 플레이어 간의 상호작용을 처리하는 메서드
void Shopkeeper::interact(Player* player) {
    std::cout << "Welcome to " << getName() << "'s shop!" << std::endl; // 상점에 온 플레이어 환영 메시지
    std::cout << getDialogue() << std::endl; // NPC의 대사 출력
    // 상점 인벤토리 표시 및 거래 처리 로직 구현 필요
}
