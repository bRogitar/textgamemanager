cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름 및 설정
project(TextGameManager)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 소스 파일 경로 설정
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*/*.cpp"
    "src/*/*/*.cpp"
)

# 헤더 파일 경로 설정 - 구체적인 경로 지정
include_directories(
    include
    include/Entities
    include/Events
    include/GameManager
    include/Interactables
    include/Interactables/Monsters
    include/Utilities
    include/World
    include/Actions
)

# 실행 파일 생성
add_executable(TextGameManager ${SOURCES})

# TinyXML2 라이브러리 추가
add_library(tinyxml2 STATIC src/tinyxml2.cpp)
target_include_directories(tinyxml2 PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(TextGameManager PRIVATE tinyxml2)

# 출력 디렉토리 설정
set_target_properties(TextGameManager PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)