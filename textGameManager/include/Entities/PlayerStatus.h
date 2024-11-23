// PlayerStatus.h
#ifndef PLAYERSTATUS_H
#define PLAYERSTATUS_H

#include <string>

class PlayerStatus {
public:
    PlayerStatus();
    void modifyHealth(int amount);
    void modifyMentalStrength(int amount);
    int getHealth() const;
    int getMentalStrength() const;

private:
    int health;
    int mentalStrength;
};

#endif // PLAYERSTATUS_H