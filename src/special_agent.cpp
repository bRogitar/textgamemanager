#include "special_agent.hpp"

CSpecialAgent::CSpecialAgent(double x, double y, double heading, double speed, double drange)
    : CAgent(x, y, heading, speed, drange)
{
}

std::string CSpecialAgent::to_string() const
{
    std::stringstream os;
    os << "[Speical Agent]";
    os << CAgent::to_string();
    return os.str();
}

// std::string CSpecialAgent::to_string() const // 오버 로딩
// {
//     std::cout << "!!!Special!!!" << std::endl;
//     return CAgent::to_string();
// }