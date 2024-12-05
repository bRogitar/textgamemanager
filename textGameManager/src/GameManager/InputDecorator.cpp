#include "InputDecorator.h"
#include <iostream>

InputDecorator::InputDecorator(InputManager* inputManager)
    : inputManager(inputManager) {}

// 사용자의 입력을 받아 처리하는 함수
std::string InputDecorator::getUserInput() {
    std::string input;

    // InputManager 객체를 통해 기본 사용자 입력을 받음
    input = inputManager->getUserInput();

    // 간단한 명령어를 전체 명령어로 확장
    if (input == "r") {
        input = "run";
    } else if (input == "f") {
        input = "fight";
    } else {
    }

    return input;
}
