#include "BaseTrap.h"

BaseTrap::BaseTrap(const std::string& id, const std::string& name, int damage)
    : id(id), name(name), damage(damage), triggered(false), visible(true) {}

std::string BaseTrap::getId() const {
    return id;
}

std::string BaseTrap::getName() const {
    return name;
}

int BaseTrap::getDamage() const {
    return damage;
}

bool BaseTrap::isTriggered() const {
    return triggered;
}

bool BaseTrap::isVisible() const {
    return visible;
}

void BaseTrap::setVisible(bool visible) {
    this->visible = visible;
}

void BaseTrap::reset() {
    triggered = false;
    visible = true;
}

bool BaseTrap::canAvoid(const Player* player) const {
    return true;
}
