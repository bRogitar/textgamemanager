#include <algorithm> // std::find 사용을 위해 포함
#include "Player.h"
#include <iostream> // 콘솔 출력을 위해 포함
#include "AbilityFactory.h"

Player::Player(const std::string& name, int health, int mentalStrength, int attackPower, int money)
    : name(name), health(health), mentalStrength(mentalStrength), attackPower(attackPower), money(money), combatHealth(health), abilityInventory() {}

void Player::setName(const std::string& name) {
    if (!name.empty()) {
        this->name = name;
    }
}

std::string Player::getName() const {
    return name;
}

void Player::setHealth(int health) {
    this->health = (health >= 0) ? health : 0;
}

int Player::getHealth() const {
    return health;
}

void Player::setMentalStrength(int mentalStrength) {
    this->mentalStrength = (mentalStrength >= 0) ? mentalStrength : 0;
}

int Player::getMentalStrength() const {
    return mentalStrength;
}

void Player::setAttackPower(int attackPower) {
    this->attackPower = (attackPower >= 0) ? attackPower : 0;
}

int Player::getAttackPower() const {
    return attackPower;
}

void Player::setMoney(int money) {
    this->money = (money >= 0) ? money : 0;
}

int Player::getMoney() const {
    return money;
}

void Player::modifyHealth(int amount) {
    setHealth(getHealth() + amount);
}

void Player::modifyMentalStrength(int amount) {
    setMentalStrength(getMentalStrength() + amount);
}

void Player::modifyAttackPower(int amount) {
    setAttackPower(getAttackPower() + amount);
}

void Player::modifyMoney(int amount) {
    setMoney(getMoney() + amount);
}


// 어빌리티 관련 함수들
void Player::addAbility(const std::string& abilityId) {
    // AbilityFactory를 사용하여 어빌리티 생성
    auto ability = AbilityFactory::getInstance().createAbility(abilityId);
    if (ability) {
        abilityInventory.addAbility(std::move(ability)); // 인벤토리에 어빌리티 추가
        std::cout << "Ability (" << abilityId << ") has been added to your inventory.\n";
    } else {
        std::cout << "Failed to create ability: " << abilityId << "\n";
    }
}
void Player::removeAbility(const std::string& abilityId) {
    abilityInventory.removeAbility(abilityId);
}

bool Player::hasAbility(const std::string& abilityId) const {
    return abilityInventory.hasAbility(abilityId);
}

const Ability* Player::getAbility(const std::string& abilityId) const {
    return abilityInventory.getAbility(abilityId);
}

void Player::useAbility(const std::string& abilityId) {
    if (hasAbility(abilityId)) {
        const Ability* ability = getAbility(abilityId);
        if (ability) {
            // 어빌리티 적용
            ability->applyEffect(*this);
            std::cout << "Used ability: " << ability->getName() << "\n";
            displayStatus();  // 사용 후 플레이어 상태 출력
        }
    } else {
        std::cout << "You do not have the ability: " << abilityId << "\n";
    }
}


void Player::displayAbilities() const {
    if (abilityInventory.isEmpty()) {
        std::cout << "No abilities available.\n";
    } else {
        std::cout << "Available Abilities:\n";
        for (const auto& ability : abilityInventory.getAbilities()) {
            std::cout << " - ID: " << ability->getAbilityId()
                      << ", Name: " << ability->getName()
                      << ", Description: " << ability->getDescription() << "\n";
        }
    }
}


bool Player::isDefeated() const {
    return health <= 0;
}

void Player::takeDamage(int damage) {
    modifyHealth(-damage);
}

void Player::applyDefeatPenalty() {
    int healthPenalty = 10;
    int mentalStrengthPenalty = 5;

    modifyHealth(-healthPenalty);
    modifyMentalStrength(-mentalStrengthPenalty);

    std::cout << "You have been defeated. Health reduced by " << healthPenalty
              << ", Mental Strength reduced by " << mentalStrengthPenalty << ".\n";
}

// 전투 관련 함수들
void Player::setCombatHealth(int health) {
    combatHealth = (health >= 0) ? health : 0;
}

int Player::getCombatHealth() const {
    return combatHealth;
}

void Player::modifyCombatHealth(int amount) {
    setCombatHealth(getCombatHealth() + amount);
}

bool Player::isCombatDefeated() const {
    return combatHealth <= 0;
}

void Player::takeCombatDamage(int damage) {
    modifyCombatHealth(-damage);
}

void Player::displayStatus() const {
    std::cout << "Player Status:\n"
              << "Name: " << name << "\n"
              << "Health: " << health << "\n"
              << "Mental Strength: " << mentalStrength << "\n"
              << "Attack Power: " << attackPower << "\n"
              << "Money: " << money << "\n"
              << "------------------------------------" << std::endl;
}
