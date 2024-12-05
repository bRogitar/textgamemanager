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

    virtual std::string getUserInput();

protected:
    InputManager() = default;
    virtual ~InputManager() = default;

    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;
};

#endif // INPUTMANAGER_H
