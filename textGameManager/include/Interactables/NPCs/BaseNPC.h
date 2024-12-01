#ifndef BASENPC_H
#define BASENPC_H

#include <string>
#include "Player.h"

// BaseNPC 클래스: NPC의 기본 기능을 정의하는 추상 클래스
class BaseNPC {
public:
    BaseNPC(const std::string& id, const std::string& name, const std::string& dialogue);

    virtual void interact(Player& player) = 0; // 상호작용 메서드, 상속받은 클래스에서 구현 필요

    std::string getId() const;
    std::string getName() const;
    std::string getDialogue() const;

protected:
    std::string id;
    std::string name;
    std::string dialogue;
};

#endif // BASENPC_H
