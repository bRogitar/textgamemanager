// PlayerStatus.h
#ifndef PLAYERSTATUS_H
#define PLAYERSTATUS_H

#include <string>

class PlayerStatus {
public:
    PlayerStatus();
    void modifyHealth(int amount);
    void modifyMentalStrength(int amount);
    void modifyAttackPonint(int amount);
    int getHealth() const;
    int getMentalStrength() const;
    int getAttackPonint() const;

private:
    int health;
    int mentalStrength;
    int attackPoint;
};

#endif // PLAYERSTATUS_H