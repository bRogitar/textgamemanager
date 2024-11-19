#include <iostream>
#include <string>
#include <vector>

#include "agent.hpp"
#include "mmanager.hpp"
#include "stochastic_decorator.hpp"
#include "simple_decorator.hpp"

#include "tinyxml2.h"

#include "special_agent.hpp"

// �ʱ�ȭ ���� Ŭ����
class InitManager
{
public:
    InitManager() {}              // �⺻ ������
    InitManager(std::string path) // ���� ��θ� �޾� �ʱ�ȭ�ϴ� ������
    {
        doc.LoadFile(path.c_str()); // XML ���� �ε�

        double x, y, heading, speed, drange;
        {
            // �Ϲ� ������Ʈ ����� XML���� �о����
            tinyxml2::XMLElement *agListElem = doc.FirstChildElement("scenario")->FirstChildElement("AgentList");
            for (tinyxml2::XMLElement *agElem = agListElem->FirstChildElement();
                 agElem != NULL; agElem = agElem->NextSiblingElement())
            {
                agElem->QueryDoubleAttribute("x", &x);
                agElem->QueryDoubleAttribute("y", &y);
                agElem->QueryDoubleAttribute("heading", &heading);
                agElem->QueryDoubleAttribute("speed", &speed);
                agElem->QueryDoubleAttribute("drange", &drange);

                // ���ο� �Ϲ� ������Ʈ ���� �� ����Ʈ�� �߰�
                CAgent *ag = new CAgent(x, y, heading, speed, drange);
                m_agentList.push_back(ag);
            }
        }

        {
            // Ư�� ������Ʈ ����� XML���� �о����
            tinyxml2::XMLElement *agListElem = doc.FirstChildElement("scenario")->FirstChildElement("SAgentList");
            for (tinyxml2::XMLElement *agElem = agListElem->FirstChildElement();
                 agElem != NULL; agElem = agElem->NextSiblingElement())
            {
                agElem->QueryDoubleAttribute("x", &x);
                agElem->QueryDoubleAttribute("y", &y);
                agElem->QueryDoubleAttribute("heading", &heading);
                agElem->QueryDoubleAttribute("speed", &speed);
                agElem->QueryDoubleAttribute("drange", &drange);

                // ���ο� Ư�� ������Ʈ ���� �� ����Ʈ�� �߰�
                CAgent *ag = new CSpecialAgent(x, y, heading, speed, drange);
                m_agentList.push_back(ag);
            }
        }
    }

    // ������Ʈ ����Ʈ ��ȯ(��ü �����͵��� ���Ϳ� ���� ������ ��ȯ)
    std::vector<CAgent *> &get_agent_list()
    {
        return m_agentList;
    }

private:
    tinyxml2::XMLDocument doc;         // XML ���� ��ü
    std::vector<CAgent *> m_agentList; // ������Ʈ ��ü���� �����ϴ� ����Ʈ
};

int main(int argc, char **argv)
{

    // �ó����� �ʱ�ȭ �Ŵ��� ��ü ����, XML ������ �̿��� ������Ʈ �ʱ�ȭ
    InitManager init_manager("test.xml");

    // �ùķ��̼� �Ŵ��� ��ü ����
    CManeuverManager mmanager;

    // �ʱ�ȭ�� ��� ������Ʈ���� �ùķ��̼� �Ŵ����� ���
    for (std::vector<CAgent *>::iterator iter = init_manager.get_agent_list().begin();
         iter != init_manager.get_agent_list().end(); ++iter)
        mmanager.register_publisher(*iter); // *iter�� �����̱� ������ �������� �ؾ��Ѵ�.

    /*
    CAgent* p_agent1 = new CAgent(10,  0, 0, 1, 10);
    p_agent1 = new StochasticDecorator(p_agent1);
    p_agent1 = new SimpleDecorator(p_agent1);

    mmanager.register_publisher(p_agent1);

    CAgent* p_agent2 = new CAgent(10,  30, 180, 1, 10);
    mmanager.register_publisher(p_agent2);
    */

    // �ùķ��̼� ���� �ʱ�ȭ �� ����
    double sim_time;
    double time_step = 1; // �ùķ��̼� �ð� ����

    for (sim_time = 0; sim_time < 30; sim_time += time_step) // 0���� 30���� �ùķ��̼� ����
    {
        // p_agent1->maneuver(time_step);
        // p_agent2->maneuver(time_step);

        // p_agent1->detect(p_agent2);
        // p_agent2->detect(p_agent1);

        mmanager.svc(time_step); // �ùķ��̼� �Ŵ��� ���� ȣ��

        // ���� �ð��� �� ������Ʈ�� ���� ���
        std::cout << "----" << std::endl;
        for (std::vector<CAgent *>::iterator iter = init_manager.get_agent_list().begin();
             iter != init_manager.get_agent_list().end(); ++iter)
            std::cout << "Time: " << sim_time << ", " << **iter << std::endl; // 84������ ������ iter�� �������� �����Ѵ�.
        // std::cout << **iter ������ ����Ǹ�:
        // operator<<�� ȣ��ǰ�,
        // operator<< ���ο��� to_string()�� ȣ��Ǹ�,
        // �̷� ���� ��ü�� ���°� ���ڿ��� ��ȯ�ǰ� ���������� std::cout�� ���

        // (*iter) => CAgent* : ������
        // *(*iter) => CAgent : ���� ��ü ����
    }
    return 0;
}

// Ŭ���̾�Ʈ �ڵ忡�� Ŭ���� Ÿ���� ���� �����ϴ� ����
// �̴� ������ �����̴�. ���� Ŭ������ �����ͷ� ���� Ŭ���� ��ü�� ������ �� ������, ��Ÿ�ӿ� ���� ��ü Ÿ�Կ� �´� �޼��尡 ȣ��ǵ��� �Ѵ�.
// CAgent�̰� CSpeicalAgent�̰� ����� ���� Ŭ������ ȣ���ϸ�, ���� ��ü�� �´� �ż��尡 ȣ��Ǳ� �����̴�.