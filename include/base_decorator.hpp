#pragma once
#include "agent.hpp"

class BaseDecorator: public CAgent
{
private:
    BaseDecorator(){};
public:
    BaseDecorator(CAgent* agent):m_wrappee(agent){};
    
public:
    virtual void maneuver(double time){ m_wrappee->maneuver(time); }
    virtual bool detect(CAgent* pTarget) = 0;

    const Pos& getPosition() const   { return m_wrappee->getPosition();}
    unsigned long getAgentID() const { return m_wrappee->getAgentID();}
    double getSpeed() const          { return m_wrappee->getSpeed();}
    double getHeading() const        { return m_wrappee->getHeading();}
    double getRange() const          { return m_wrappee->getRange();}
protected:
    CAgent* m_wrappee;
};