#ifndef SHOPKEEPER_H
#define SHOPKEEPER_H

#include "BaseNPC.h"
#include "Ability.h"
#include <vector>

class Shopkeeper : public BaseNPC {
public:
    Shopkeeper(const std::string& id, const std::string& name, const std::string& dialogue);
    void interact(Player& player) override;

private:
    bool sellAbility(Player& player, const std::string& abilityId, int price);
};

#endif