cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름 설정
project(TextGameManager)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 소스 파일 목록 추가
set(SOURCES
    src/main.cpp
    src/Entities/Ability.cpp
    src/Entities/AbilityInventory.cpp
    src/Entities/Item.cpp
    src/Entities/ItemInventory.cpp
    src/Entities/Player.cpp
    src/Events/Choice.cpp
    src/Events/Event.cpp
    src/GameManager/CombatManager.cpp
    src/GameManager/EventManager.cpp
    src/GameManager/GameManager.cpp
    src/GameManager/InputManager.cpp
    src/GameManager/InteractionManager.cpp
    src/GameManager/SaveLoadManager.cpp
    src/Interactables/BaseInteractable.cpp
    src/Interactables/InteractableFactory.cpp
    src/Interactables/Monsters/BaseMonster.cpp
    src/World/Room.cpp
    src/World/WorldMap.cpp
    src/tinyxml2.cpp # tinyxml2 소스 파일 추가
    src/Interactables/Monsters/Goblin.cpp          # 추가된 부분
    src/Interactables/Monsters/MonsterFactory.cpp  
)

# 헤더 파일 경로 설정
include_directories(
    include
    include/Commands
    include/Entities
    include/Events
    include/GameManager
    include/Interactables
    include/Utilities
    include/World
    include/Interactables/Monsters
)

# 실행 파일 생성
add_executable(TextGameManager ${SOURCES})

# TinyXML2 소스를 직접 추가하여 라이브러리로 링크
add_library(tinyxml2 STATIC src/tinyxml2.cpp)
target_link_libraries(TextGameManager PRIVATE tinyxml2)

# 출력 디렉토리 설정 (옵션)
set_target_properties(TextGameManager PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
