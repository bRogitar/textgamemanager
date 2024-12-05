#ifndef INPUTDECORATOR_H
#define INPUTDECORATOR_H

#include "InputManager.h"
#include <string>

class InputDecorator : public InputManager {
public:
    // 생성자의 정의를 제거하고 선언만 유지
    InputDecorator(InputManager* inputManager);

    // 부모 클래스의 가상 함수를 정확히 재정의
    std::string getUserInput() override;

private:
    InputManager* inputManager;
};

#endif // INPUTDECORATOR_H
