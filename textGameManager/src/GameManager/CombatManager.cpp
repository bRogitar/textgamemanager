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

        // Set combat health to current health
        player.setCombatHealth(player.getHealth());
        monster->setCombatHealth(monster->getHealth());

        combatLoop();
    } else {
        std::cout << "No monster to fight!" << std::endl;
    }
}

// Combat Loop Logic
void CombatManager::combatLoop() {
    while (!player.isCombatDefeated() && !monster->isCombatDefeated()) {
        playerAttack();  // Player attacks monster
        if (monster->isCombatDefeated()) {
            std::cout << "You have defeated the " << monster->getName() << "!" << std::endl;
            break;
        }
        
        monsterAttack();  // Monster attacks player
        if (player.isCombatDefeated()) {
            std::cout << "You have been defeated by the " << monster->getName() << "!" << std::endl;
            player.applyDefeatPenalty(); // Apply penalty to player after defeat
            break;
        }

        displayCombatStatus();  // Display the combat status after each turn
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Pause for 1 second between actions
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
