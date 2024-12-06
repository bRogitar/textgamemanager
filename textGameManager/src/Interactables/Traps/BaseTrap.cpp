//BaseTrap.cpp

#include "BaseTrap.h"
#include <iostream>

BaseTrap::BaseTrap(const std::string& name, int damage)
    : name(name), damage(damage) {}

const std::string& BaseTrap::getName() const {
    return name;
}

int BaseTrap::getDamage() const {
    return damage;
}

void BaseTrap::setAttributes(const std::string& newName, int newDamage) {
    name = newName;
    damage = newDamage;
}