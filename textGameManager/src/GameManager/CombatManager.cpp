#include "CombatManager.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "BaseMonster.h"
#include "Player.h"  // Player 클래스 포함

// CombatManager Constructor
CombatManager::CombatManager(Player& player, BaseMonster* monster)
    : player(player), monster(monster) {}

// Start Combat Function
void CombatManager::startCombat() {
    if (monster != nullptr) {
        std::cout << "Combat with " << monster->getName() << " started!" << std::endl;

        // 플레이어와 몬스터의 상태를 표시
        player.displayStatus();
        monster->displayStatus();

        // Set combat health to current health
        player.setCombatHealth(player.getHealth());
        combatLoop();
    } else {
        std::cout << "No monster to fight!" << std::endl;
    }
}

// Combat Loop Logic
void CombatManager::combatLoop() {
    while (!player.isCombatDefeated() && !monster->isCombatDefeated()) {
        playerAttack();  // Player attacks monster
        displayCombatStatus();  // Display combat status after player's attack

        if (monster->isCombatDefeated()) {
            std::cout << "You have defeated the " << monster->getName() << "!" << std::endl;
            break;
        }
        
        monsterAttack();  // Monster attacks player
        displayCombatStatus();  // Display combat status after monster's attack

        if (player.isCombatDefeated()) {
            std::cout << "You have been defeated by the " << monster->getName() << "!" << std::endl;
            player.applyDefeatPenalty(); // Apply penalty to player after defeat
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1)); // Pause for 1 second between actions
        std::cout << "------------------------------------" << std::endl;
    }
}

// Player Attack Function
void CombatManager::playerAttack() {
    int damage = player.getAttackPower();
    monster->takeCombatDamage(damage);
    std::cout << "You attack the " << monster->getName() << " for " << damage << " damage." << std::endl;
}

// Monster Attack Function
void CombatManager::monsterAttack() {
    int damage = monster->getAttackPower();
    player.takeCombatDamage(damage);
    std::cout << monster->getName() << " attacks you for " << damage << " damage." << std::endl;
}

// Display Combat Status Function
void CombatManager::displayCombatStatus() const {
    // Display both player's and monster's current health
    std::cout << "Player Combat Health: " << player.getCombatHealth() 
              << " | Monster Health: " << monster->getHealth() << std::endl;
}
