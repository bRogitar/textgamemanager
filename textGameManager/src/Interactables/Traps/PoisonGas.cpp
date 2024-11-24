#include "PoisonGasTrap.h"
#include <iostream>

PoisonGasTrap::PoisonGasTrap(const std::string& id, const std::string& name, int damage, int poisonDuration, int poisonDamagePerTurn)
    : BaseTrap(id, name, damage), poisonDuration(poisonDuration), poisonDamagePerTurn(poisonDamagePerTurn) {}

void PoisonGasTrap::trigger(Player* player) {
    if (player) {
        std::cout << getName() << " 독가스 함정이 발동되었습니다! 플레이어가 " << getDamage() << "의 피해를 입습니다.\n";
        player->modifyHealth(-getDamage());

        // Apply poison effect over multiple turns.
        for (int i = 0; i < poisonDuration; ++i) {
            player->modifyHealth(-poisonDamagePerTurn);
            std::cout << "플레이어가 독으로 인해 " << poisonDamagePerTurn << "의 피해를 추가로 입습니다. (턴 " << (i + 1) << ")\n";
        }

        triggered = true;
    }
}

bool PoisonGasTrap::canAvoid(const Player* player) const {
    // 독가스 트랩은 특별한 능력이 없으면 피할 수 없음.
    return false;
}

int PoisonGasTrap::getPoisonDuration() const {
    return poisonDuration;
}

int PoisonGasTrap::getPoisonDamagePerTurn() const {
    return poisonDamagePerTurn;
}
