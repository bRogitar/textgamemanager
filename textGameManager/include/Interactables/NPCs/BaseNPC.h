// BaseNPC.h

#ifndef BASENPC_H
#define BASENPC_H

#include <memory>
#include <string>

class Player;

class BaseNPC {
public:
    virtual ~BaseNPC() = default;
    BaseNPC(const std::string& name, const std::string& dialog);

    virtual void interact(Player& player) = 0;
    virtual std::unique_ptr<BaseNPC> clone() const = 0;

    const std::string& getName() const;
    const std::string& getDialog() const;
    void setAttributes(const std::string& name, const std::string& dialog);

protected:
    std::string name;
    std::string dialog;
};

#endif