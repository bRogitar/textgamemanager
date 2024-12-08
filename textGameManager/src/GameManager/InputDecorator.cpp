#include "InputDecorator.h"
#include <limits>
#include <iostream>
#include <algorithm>
#include "Choice.h"

InputDecorator::InputDecorator(InputManager* inputManager)
    : inputManager(inputManager) {}

// 사용자의 입력을 받아 처리하는 함수
std::string InputDecorator::getUserInput() {
    std::string input;

    // InputManager 객체를 통해 기본 사용자 입력을 받음
    input = inputManager->getUserInput();

    // 간단한 명령어를 전체 명령어로 확장
    // if (input == "r") {
    //     input = "run";
    // } else if (input == "f") {
    //     input = "fight";
    // } else if (input == "s"){
    //     input = "save";
    // } else if (input == "n"){
    //     input = "no";
    // } else if (input == "y"){
    //     input = "yes";
    // }

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