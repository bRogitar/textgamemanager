#pragma once
#include <sstream>

#include "agent.hpp"

class CSpecialAgent : public CAgent
{
public:
    CSpecialAgent(double x, double y, double heading, double speed, double drange);

public:
    virtual std::string to_string() const;
};