#include <iostream>
#include <string>
#include <vector>

#include "agent.hpp"
#include "mmanager.hpp"
#include "stochastic_decorator.hpp"
#include "simple_decorator.hpp"

#include "tinyxml2.h"

#include "special_agent.hpp"

// 초기화 관리 클래스
class InitManager
{
public:
    InitManager() {}              // 기본 생성자
    InitManager(std::string path) // 파일 경로를 받아 초기화하는 생성자
    {
        doc.LoadFile(path.c_str()); // XML 파일 로드

        double x, y, heading, speed, drange;
        {
            // 일반 에이전트 목록을 XML에서 읽어들임
            tinyxml2::XMLElement *agListElem = doc.FirstChildElement("scenario")->FirstChildElement("AgentList");
            for (tinyxml2::XMLElement *agElem = agListElem->FirstChildElement();
                 agElem != NULL; agElem = agElem->NextSiblingElement())
            {
                agElem->QueryDoubleAttribute("x", &x);
                agElem->QueryDoubleAttribute("y", &y);
                agElem->QueryDoubleAttribute("heading", &heading);
                agElem->QueryDoubleAttribute("speed", &speed);
                agElem->QueryDoubleAttribute("drange", &drange);

                // 새로운 일반 에이전트 생성 후 리스트에 추가
                CAgent *ag = new CAgent(x, y, heading, speed, drange);
                m_agentList.push_back(ag);
            }
        }

        {
            // 특수 에이전트 목록을 XML에서 읽어들임
            tinyxml2::XMLElement *agListElem = doc.FirstChildElement("scenario")->FirstChildElement("SAgentList");
            for (tinyxml2::XMLElement *agElem = agListElem->FirstChildElement();
                 agElem != NULL; agElem = agElem->NextSiblingElement())
            {
                agElem->QueryDoubleAttribute("x", &x);
                agElem->QueryDoubleAttribute("y", &y);
                agElem->QueryDoubleAttribute("heading", &heading);
                agElem->QueryDoubleAttribute("speed", &speed);
                agElem->QueryDoubleAttribute("drange", &drange);

                // 새로운 특수 에이전트 생성 후 리스트에 추가
                CAgent *ag = new CSpecialAgent(x, y, heading, speed, drange);
                m_agentList.push_back(ag);
            }
        }
    }

    // 에이전트 리스트 반환(객체 포인터들의 벡터에 대한 참조를 반환)
    std::vector<CAgent *> &get_agent_list()
    {
        return m_agentList;
    }

private:
    tinyxml2::XMLDocument doc;         // XML 문서 객체
    std::vector<CAgent *> m_agentList; // 에이전트 객체들을 저장하는 리스트
};

int main(int argc, char **argv)
{

    // 시나리오 초기화 매니저 객체 생성, XML 파일을 이용해 에이전트 초기화
    InitManager init_manager("test.xml");

    // 시뮬레이션 매니저 객체 생성
    CManeuverManager mmanager;

    // 초기화된 모든 에이전트들을 시뮬레이션 매니저에 등록
    for (std::vector<CAgent *>::iterator iter = init_manager.get_agent_list().begin();
         iter != init_manager.get_agent_list().end(); ++iter)
        mmanager.register_publisher(*iter); // *iter는 참조이기 때문에 역참조를 해야한다.

    /*
    CAgent* p_agent1 = new CAgent(10,  0, 0, 1, 10);
    p_agent1 = new StochasticDecorator(p_agent1);
    p_agent1 = new SimpleDecorator(p_agent1);

    mmanager.register_publisher(p_agent1);

    CAgent* p_agent2 = new CAgent(10,  30, 180, 1, 10);
    mmanager.register_publisher(p_agent2);
    */

    // 시뮬레이션 엔진 초기화 및 실행
    double sim_time;
    double time_step = 1; // 시뮬레이션 시간 간격

    for (sim_time = 0; sim_time < 30; sim_time += time_step) // 0부터 30까지 시뮬레이션 실행
    {
        // p_agent1->maneuver(time_step);
        // p_agent2->maneuver(time_step);

        // p_agent1->detect(p_agent2);
        // p_agent2->detect(p_agent1);

        mmanager.svc(time_step); // 시뮬레이션 매니저 서비스 호출

        // 현재 시간과 각 에이전트의 상태 출력
        std::cout << "----" << std::endl;
        for (std::vector<CAgent *>::iterator iter = init_manager.get_agent_list().begin();
             iter != init_manager.get_agent_list().end(); ++iter)
            std::cout << "Time: " << sim_time << ", " << **iter << std::endl; // 84번에서 참조한 iter를 역참조를 수행한다.
        // std::cout << **iter 구문이 실행되면:
        // operator<<가 호출되고,
        // operator<< 내부에서 to_string()이 호출되며,
        // 이로 인해 객체의 상태가 문자열로 변환되고 최종적으로 std::cout에 출력

        // (*iter) => CAgent* : 포인터
        // *(*iter) => CAgent : 실제 객체 참조
    }
    return 0;
}

// 클라이언트 코드에서 클래스 타입을 몰라도 동작하는 이유
// 이는 다형성 때문이다. 상위 클래스의 포인터로 하위 클래스 객체를 참조할 수 있으며, 런타임에 실제 객체 타입에 맞는 메서드가 호출되도록 한다.
// CAgent이건 CSpeicalAgent이건 공통된 상위 클래스를 호출하면, 실제 객체에 맞는 매서드가 호출되기 때문이다.