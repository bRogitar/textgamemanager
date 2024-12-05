// CombatManager.cpp
#include "CombatManager.h"
#include <iostream>
#include <windows.h>
#include "BaseMonster.h"
#include "Player.h"

CombatManager::CombatManager(Player& player, BaseMonster* monster)
    : player(player), monster(monster) {}

void CombatManager::startCombat() {
    if (monster != nullptr) {
        std::cout << "Combat with " << monster->getName() << " started!" << std::endl;

        // 플레이어와 몬스터의 상태를 표시
        player.displayStatus();
        monster->displayStatus();

        // Set combat health to current health
        player.setCombatHealth(player.getHealth());
        monster->setHealth(monster->getHealth());  // Changed from setCombatHealth

        combatLoop();
    } else {
        std::cout << "No monster to fight!" << std::endl;
    }
}

void CombatManager::combatLoop() {
    while (!player.isCombatDefeated() && !monster->isCombatDefeated()) {
        playerAttack();
        displayCombatStatus();

        if (monster->isCombatDefeated()) {
            std::cout << "You have defeated the " << monster->getName() << "!" << std::endl;
            break;
        }
        
        monsterAttack();
        displayCombatStatus();

        if (player.isCombatDefeated()) {
            std::cout << "You have been defeated by the " << monster->getName() << "!" << std::endl;
            player.applyDefeatPenalty();
            break;
        }

        Sleep(1000);
        std::cout << "------------------------------------" << std::endl;
    }
}

void CombatManager::playerAttack() {
    int damage = player.getAttackPower();
    monster->takeCombatDamage(damage);
    std::cout << "You attack the " << monster->getName() << " for " << damage << " damage." << std::endl;
}

void CombatManager::monsterAttack() {
    int damage = monster->getAttackPower();
    player.takeCombatDamage(damage);
    std::cout << monster->getName() << " attacks you for " << damage << " damage." << std::endl;
}

void CombatManager::displayCombatStatus() const {
    std::cout << "Player Combat Health: " << player.getCombatHealth() 
              << " | Monster Health: " << monster->getHealth() << std::endl;  // Changed from getCombatHealth
}