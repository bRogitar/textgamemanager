#include "InputManager.h"
#include <limits>
#include <iostream>
#include <algorithm>
#include "Choice.h"

// 기본 사용자 입력을 받아오는 함수
std::string InputManager::getUserInput() {
    std::string input;

    // 유효한 입력이 들어올 때까지 반복
    while (true) {
        std::getline(std::cin, input);

        input.erase(0, input.find_first_not_of(" \t\n\r\f\v")); // 왼쪽 공백 제거
        input.erase(input.find_last_not_of(" \t\n\r\f\v") + 1); // 오른쪽 공백 제거

        if (input.empty()) {
            std::cout << "[DEBUG] Empty input received, please enter a valid command: ";
        } else {
            break; // 유효한 입력을 받으면 루프 종료
        }
    }

    return input;
}

