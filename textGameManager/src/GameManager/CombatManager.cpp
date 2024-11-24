#include "CombatManager.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "BaseMonster.h"

#include "CombatManager.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "BaseMonster.h"

// CombatManager Constructor
CombatManager::CombatManager(Player& player, BaseMonster* monster)
    : player(player), monster(monster) {}

// Start Combat Function
void CombatManager::startCombat() {
    if (monster != nullptr) {
        std::cout << "Combat with " << monster->getName() << " started!" << std::endl;
        player.setCombatHealth(player.getHealth()); // Set combat health to current health
        monster->setCombatHealth(monster->getHealth()); // Set combat health to current health
        combatLoop();
    } else {
        std::cout << "No monster to fight!" << std::endl;
    }
}


// Combat Loop Logic
void CombatManager::combatLoop() {
    while (!player.isCombatDefeated() && !monster->isCombatDefeated()) {
        playerAttack();  // 플레이어가 몬스터를 공격
        if (monster->isCombatDefeated()) {
            std::cout << "You have defeated the " << monster->getName() << "!" << std::endl;
            break;
        }
        
        monsterAttack();  // 몬스터가 플레이어를 공격
        if (player.isCombatDefeated()) {
            std::cout << "You have been defeated by the " << monster->getName() << "!" << std::endl;
            player.applyDefeatPenalty(); // 플레이어 패배 시 패널티 적용 (체력 및 정신력 감소)
            break;
        }

        displayCombatStatus();  // 전투 상태 출력
        std::this_thread::sleep_for(std::chrono::seconds(1)); // 1초 대기
    }
}

// Player Attack Function
void CombatManager::playerAttack() {
    monster->takeCombatDamage(player.getAttackPower());
    std::cout << "You attack the " << monster->getName() << " for " << player.getAttackPower() << " damage." << std::endl;
}

// Monster Attack Function
void CombatManager::monsterAttack() {
    player.takeCombatDamage(monster->getAttackPower());
    std::cout << monster->getName() << " attacks you for " << monster->getAttackPower() << " damage." << std::endl;
}

// Display Combat Status Function
void CombatManager::displayCombatStatus() const {
    std::cout << "Player Combat Health: " << player.getCombatHealth() 
              << " | Monster Combat Health: " << monster->getCombatHealth() << std::endl;
}