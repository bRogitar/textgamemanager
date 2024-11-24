#include "BaseNPC.h"

// BaseNPC 생성자: NPC의 ID, 이름, 대사를 초기화하고 상호작용 가능 여부를 true로 설정
BaseNPC::BaseNPC(const std::string& id, const std::string& name, const std::string& dialogue)
    : id(id), name(name), dialogue(dialogue), isInteractable(true) {}

// NPC의 ID를 반환하는 메서드
std::string BaseNPC::getId() const {
    return id;
}

// NPC의 이름을 반환하는 메서드
std::string BaseNPC::getName() const {
    return name;
}

// NPC의 현재 대사를 반환하는 메서드
std::string BaseNPC::getDialogue() const {
    return dialogue;
}

// NPC의 대사를 새로운 대사로 설정하는 메서드
void BaseNPC::setDialogue(const std::string& newDialogue) {
    dialogue = newDialogue;
}

// NPC의 이름을 새로운 이름으로 설정하는 메서드
void BaseNPC::setName(const std::string& newName) {
    name = newName;
}

// 플레이어가 NPC와 상호작용할 수 있는지 확인하는 메서드 (기본적으로 true 반환)
bool BaseNPC::canInteract(const Player* player) const {
    return isInteractable;
}
