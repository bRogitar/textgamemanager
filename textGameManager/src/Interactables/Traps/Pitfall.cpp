#include "Pitfall.h"
#include <iostream>

Pitfall::Pitfall(const std::string& id, const std::string& name, int damage, int depth)
    : BaseTrap(id, name, damage), depth(depth) {}

void Pitfall::trigger(Player* player) {
    if (player) {
        std::cout << getName() << " 함정이 발동되었습니다! 플레이어가 " << getDamage() << "의 피해를 입습니다.\n";
        player->modifyHealth(-getDamage());
        triggered = true;
    }
}

int Pitfall::getDepth() const {
    return depth;
}
