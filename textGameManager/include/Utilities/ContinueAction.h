#ifndef CONTINUEACTION_H
#define CONTINUEACTION_H

#include "BaseAction.h"
#include <iostream>

class ContinueAction : public BaseAction {
public:
    void execute(Player& player) override {
        std::cout << "You continue forward through the mist..." << std::endl;
    }
};
#endif