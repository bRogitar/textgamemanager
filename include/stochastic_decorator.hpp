#pragma once
#include "base_decorator.hpp"

class StochasticDecorator: public BaseDecorator
{
public:
    StochasticDecorator(CAgent* agent):BaseDecorator(agent){};
    
public:
    virtual bool detect(CAgent* pTarget){
        std::cout << "Stochastic Decorator" << std::endl;
        return m_wrappee->detect(pTarget);
    };
};