#ifndef BASENPC_H
#define BASENPC_H

#include <string>
#include <vector>
#include "../../Entities/Player.h"

class BaseNPC {
public:
    BaseNPC(const std::string& id, const std::string& name, const std::string& dialogue);

    // Getter methods
    std::string getId() const;
    std::string getName() const;
    std::string getDialogue() const;

    // Setter methods
    void setDialogue(const std::string& dialogue);
    void setName(const std::string& name);

    // Interaction methods
    virtual void interact(Player* player) = 0;
    virtual bool canInteract(const Player* player) const;

protected:
    std::string id;
    std::string name;
    std::string dialogue;
    bool isInteractable;
};

#endif // BASENPC_H