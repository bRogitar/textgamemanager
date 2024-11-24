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
    // 기본적으로는 플레이어가 트랩을 피할 수 있는지 여부를 반환 
    // 하위 클래스에서 필요에 따라 오버라이드
    return true;
}
