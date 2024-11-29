#ifndef MENTALPOTION_H
#define MENTALPOTION_H

#include "BaseItem.h"

class MentalPotion : public Item {
public:
    MentalPotion() : Item("mental_potion", "Mental Potion", "Restores 30 mental strength.", true) {
        addEffect("mental", 30);
    }
};

#endif // MENTALPOTION_H 