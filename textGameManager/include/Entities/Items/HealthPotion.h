#ifndef HEALTHPOTION_H
#define HEALTHPOTION_H

#include "BaseItem.h"

class HealthPotion : public BaseItem {
public:
    HealthPotion() : BaseItem("health_potion", "Health Potion", "Restores 50 health.", true) {
        addEffect("health", 50);
    }
};

#endif // HEALTHPOTION_H 