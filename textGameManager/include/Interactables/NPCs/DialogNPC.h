#ifndef DIALOGNPC_H
#define DIALOGNPC_H

#include "BaseNPC.h"
#include "Player.h"

class DialogNPC : public BaseNPC {
public:
    DialogNPC(const std::string& name, const std::string& dialog);
    
    void interact(Player& player) override;
    std::unique_ptr<BaseNPC> clone() const override;
};

#endif // DIALOGNPC_H