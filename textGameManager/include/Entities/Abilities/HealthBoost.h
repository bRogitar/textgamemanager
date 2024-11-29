#ifndef HEALTHBOOST_H
#define HEALTHBOOST_H

#include "BaseAbility.h"

class HealthBoost : public Ability {
public:
    HealthBoost() : Ability(
        "health_boost", 
        "Health Boost", 
        "Increases health by 20.", 0) {}
};

#endif // HEALTHBOOST_H 