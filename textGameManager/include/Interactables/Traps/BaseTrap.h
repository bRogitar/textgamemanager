//BaseTrap.h

#ifndef BASETRAP_H
#define BASETRAP_H

#include <memory>
#include <string>

class Player;

class BaseTrap {
public:
    virtual ~BaseTrap() = default;
    BaseTrap(const std::string& name, int damage);

    virtual void trigger(Player& player) = 0;
    virtual std::unique_ptr<BaseTrap> clone() const = 0;

    const std::string& getName() const;
    int getDamage() const;
    void setAttributes(const std::string& name, int damage);

protected:
    std::string name;
    int damage;
};

#endif