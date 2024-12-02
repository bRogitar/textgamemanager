#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <string>

class InputManager {
public:
    static InputManager& getInstance();
    std::string getUserInput();
private:
    InputManager() = default;
    ~InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;
};

#endif // INPUTMANAGER_H