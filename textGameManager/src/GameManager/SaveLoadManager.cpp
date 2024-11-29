// #include "SaveLoadManager.h"
// #include "tinyxml2.h"
// #include <iostream>
// #include <fstream>

// #define SAVE_DIRECTORY "./saves/"

// using namespace tinyxml2;

// SaveLoadManager& SaveLoadManager::getInstance() {
//     static SaveLoadManager instance;
//     return instance;
// }

// SaveLoadManager::SaveLoadManager() {}

// bool SaveLoadManager::saveGame(const Player& player, const std::string& filename) {
//     XMLDocument doc;
//     XMLNode* root = doc.NewElement("SaveGame");
//     doc.InsertFirstChild(root);

//     // Save player data
//     XMLElement* playerElement = doc.NewElement("Player");
//     playerElement->SetAttribute("name", player.getName().c_str());
//     playerElement->SetAttribute("health", player.getHealth());
//     playerElement->SetAttribute("mentalStrength", player.getMentalStrength());
//     playerElement->SetAttribute("attackPower", player.getAttackPower());
//     playerElement->SetAttribute("money", player.getMoney());
//     root->InsertEndChild(playerElement);

//     // Save inventory
//     XMLElement* inventoryElement = doc.NewElement("Inventory");
//     for (const auto& item : player.getItemInventory().getItems()) {
//         XMLElement* itemElement = doc.NewElement("Item");
//         itemElement->SetAttribute("id", item.getId().c_str());
//         itemElement->SetAttribute("name", item.getName().c_str());
//         inventoryElement->InsertEndChild(itemElement);
//     }
//     root->InsertEndChild(inventoryElement);

//     // Save abilities
//     XMLElement* abilitiesElement = doc.NewElement("Abilities");
//     for (const auto& ability : player.getAbilityInventory().getAbilities()) {
//         XMLElement* abilityElement = doc.NewElement("Ability");
//         abilityElement->SetAttribute("id", ability.getId().c_str());
//         abilityElement->SetAttribute("name", ability.getName().c_str());
//         abilitiesElement->InsertEndChild(abilityElement);
//     }
//     root->InsertEndChild(abilitiesElement);

//     // Save file
//     XMLError eResult = doc.SaveFile((SAVE_DIRECTORY + filename).c_str());
//     if (eResult != XML_SUCCESS) {
//         std::cout << "Error saving game to " << filename << std::endl;
//         return false;
//     }
//     std::cout << "Game saved successfully to " << filename << std::endl;
//     return true;
// }

// bool SaveLoadManager::loadGame(Player& player, const std::string& filename) {
//     XMLDocument doc;
//     XMLError eResult = doc.LoadFile((SAVE_DIRECTORY + filename).c_str());
//     if (eResult != XML_SUCCESS) {
//         std::cout << "Error loading game from " << filename << std::endl;
//         return false;
//     }

//     // Load player data
//     XMLElement* playerElement = doc.FirstChildElement("SaveGame")->FirstChildElement("Player");
//     if (playerElement) {
//         player.setName(playerElement->Attribute("name") ? playerElement->Attribute("name") : "Unknown");
//         int health;
//         playerElement->QueryIntAttribute("health", &health);
//         player.setHealth(health);

//         int mentalStrength;
//         playerElement->QueryIntAttribute("mentalStrength", &mentalStrength);
//         player.setMentalStrength(mentalStrength);

//         int attackPower;
//         playerElement->QueryIntAttribute("attackPower", &attackPower);
//         player.setAttackPower(attackPower);

//         int money;
//         playerElement->QueryIntAttribute("money", &money);
//         player.setMoney(money);
//     }

//     // Load inventory
//     XMLElement* inventoryElement = doc.FirstChildElement("SaveGame")->FirstChildElement("Inventory");
//     if (inventoryElement) {
//         for (XMLElement* itemElement = inventoryElement->FirstChildElement("Item"); itemElement != nullptr; itemElement = itemElement->NextSiblingElement("Item")) {
//             std::string itemId = itemElement->Attribute("id") ? itemElement->Attribute("id") : "Unknown";
//             std::string itemName = itemElement->Attribute("name") ? itemElement->Attribute("name") : "Unknown";
//             Item item(itemId, itemName);
//             player.addItem(item);
//         }
//     }

//     // Load abilities
//     XMLElement* abilitiesElement = doc.FirstChildElement("SaveGame")->FirstChildElement("Abilities");
//     if (abilitiesElement) {
//         for (XMLElement* abilityElement = abilitiesElement->FirstChildElement("Ability"); abilityElement != nullptr; abilityElement = abilityElement->NextSiblingElement("Ability")) {
//             std::string abilityId = abilityElement->Attribute("id") ? abilityElement->Attribute("id") : "Unknown";
//             std::string abilityName = abilityElement->Attribute("name") ? abilityElement->Attribute("name") : "Unknown";
//             Ability ability(abilityId, abilityName);
//             player.addAbility(ability);
//         }
//     }

//     std::cout << "Game loaded successfully from " << filename << std::endl;
//     return true;
// }
