#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <string>
#include <iostream>

class InputManager {
public:
    static InputManager* getInstance() {
        static InputManager instance;
        return &instance;
    }

    // 기본 입력
    virtual std::string getUserInput();
    
    // Choice 입력 (Event 에서 사용)
    std::string getChoiceInput(const std::vector<Choice>& choices);
    
    // Yes/No 입력
    std::string getYesNoInput();

protected:
    InputManager() = default;
    virtual ~InputManager() = default;

    // 입력 문자 전처리
    std::string preprocessInput(const std::string& input);

    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;
};

#endif
