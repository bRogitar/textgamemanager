# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.30
cmake_policy(SET CMP0009 NEW)

# SOURCES at CMakeLists.txt:11 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "D:/TextAdventures/textgamemanager/textGameManager/src/*.cpp")
set(OLD_GLOB
  "D:/TextAdventures/textgamemanager/textGameManager/src/Commands/Command.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Commands/CommandParser.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Entities/Ability.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Entities/AbilityInventory.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Entities/Item.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Entities/ItemInventory.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Entities/Player.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Events/Choice.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Events/Event.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/GameManager/CombatManager.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/GameManager/EventManager.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/GameManager/GameManager.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Interactables/BaseInteractable.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Interactables/InteractableFactory.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Interactables/Monsters/BaseMonster.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Interactables/Monsters/Dragon.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Interactables/Monsters/Goblin.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Interactables/Monsters/MonsterFactory.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Interactables/NPCs/BaseNPC.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Interactables/NPCs/QuestGiver.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Interactables/NPCs/Shopkeeper.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Interactables/Traps/BaseTrap.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Interactables/Traps/Pitfall.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Interactables/Traps/PoisonGas.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/Utilities/FightAction.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/World/Room.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/World/WorldMap.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/main.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/test.cpp"
  "D:/TextAdventures/textgamemanager/textGameManager/src/tinyxml2.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "D:/TextAdventures/textgamemanager/textGameManager/build/CMakeFiles/cmake.verify_globs")
endif()
