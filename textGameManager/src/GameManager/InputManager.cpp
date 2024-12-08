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

// 입력 문자 전처리
std::string InputManager::preprocessInput(const std::string& input) {
    std::string processed = input;
    std::transform(processed.begin(), processed.end(), 
                  processed.begin(), ::tolower);
    return processed;
}

// Choice 입력, 전체 id나 첫 글자만으로 선택처리
std::string InputManager::getChoiceInput(const std::vector<Choice>& choices) {
    while (true) {
        std::cout << "Enter your choice: ";
        std::string input = preprocessInput(getUserInput());
        
        auto it = std::find_if(choices.begin(), choices.end(),
            [&](const Choice& choice) { 
                std::string fullId = preprocessInput(choice.getId());
                return fullId == input || 
                       (input.length() == 1 && fullId[0] == input[0]);
            });

        if (it != choices.end()) {
            return it->getId();
        }
        std::cout << "Invalid choice. Please try again." << std::endl;
    }
}

// Yes/No 입력
std::string InputManager::getYesNoInput() {
    while (true) {
        std::string input = preprocessInput(getUserInput());
        
        if (input == "y" || input == "yes") {
            return "yes";
        } else if (input == "n" || input == "no") {
            return "no";
        }
        
        std::cout << "Invalid choice. Please enter 'yes' or 'no': ";
    }
}