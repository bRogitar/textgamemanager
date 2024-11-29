#ifndef HEALTHPOTION_H
#define HEALTHPOTION_H

#include "Item.h"

class HealthPotion : public Item {
public:
    HealthPotion() : Item("health_potion", "Health Potion", "Restores 50 health.", true) {
        addEffect("health", 50);
    }
};

#endif // HEALTHPOTION_H 