#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

// IInteractable.h
#ifndef IINTERACTABLE_H
#define IINTERACTABLE_H

#include <string>

class IInteractable {
public:
    virtual ~IInteractable() = default;
    virtual std::string getInteractableId() const = 0;
    virtual void interact() = 0;
};

#endif // IINTERACTABLE_H