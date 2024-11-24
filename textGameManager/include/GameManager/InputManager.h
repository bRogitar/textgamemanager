#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <string>
#include <vector>

class InputManager {
public:
    static InputManager& getInstance();
    std::string getInput();
    int getChoice(const std::vector<std::string>& options);
    bool confirmAction(const std::string& message);
    void clearInput();

private:
    InputManager();
    ~InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    bool validateInput(const std::string& input, int optionsCount) const;
    void displayPrompt() const;
};

#endif // INPUTMANAGER_H