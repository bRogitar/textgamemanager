#include "Shopkeeper.h"
#include "AbilityFactory.h"
#include <iostream>

Shopkeeper::Shopkeeper(const std::string& id, const std::string& name, const std::string& dialogue)
    : BaseNPC(id, name, dialogue) {}

bool Shopkeeper::sellAbility(Player& player, const std::string& abilityId, int price) {
    if (player.hasAbility(abilityId)) {
        std::cout << "너에겐 필요 없는거 같은데?" << std::endl;
        return false;
    }
    
    if (player.getMoney() >= price) {
        auto ability = AbilityFactory::createAbility(abilityId);
        if (ability) {
            player.modifyMoney(-price);
            player.addAbility(*ability);
            std::cout << ability->getName() << "을(를) 구매했습니다!" << std::endl;
            return true;
        }
    }
    std::cout << "돈이 부족한데?" << std::endl;
    return false;
}

void Shopkeeper::interact(Player& player) {
    std::cout << "\n=== " << getName() << "의 상점 ===" << std::endl;
    std::cout << getDialogue() << std::endl;
    
    while (true) {
        std::cout << "\n현재 소지금: " << player.getMoney() << std::endl;
        std::cout << "1. 무식하게 큰 대검 구매 (가격: 1)" << std::endl;
        std::cout << "2. 세계함정도감 구매 (가격: 1)" << std::endl;
        std::cout << "3. 상점 나가기" << std::endl;
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                sellAbility(player, "greatsword", 1);
                break;
            case 2:
                sellAbility(player, "trap_codex", 1);
                break;
            case 3:
                std::cout << "지금은 구매할게 없어" << std::endl;
                return;
            default:
                std::cout << "잘못된 선택입니다." << std::endl;
                break;
        }
    }
}