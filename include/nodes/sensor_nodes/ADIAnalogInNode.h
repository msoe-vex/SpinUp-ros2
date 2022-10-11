#pragma once

#include "nodes/NodeManager.h"
#include "api.h"

class ADIAnalogInNode : public Node {
private:
    pros::ADIAnalogIn m_analog_in;
    std::string m_handle_name;

    bool m_is_reversed;

    void m_populateMessage();

    void m_publishData(const std_msgs::Empty& msg);

public:
    ADIAnalogInNode(NodeManager* node_manager, int port, std::string handle_name, bool reverse=false);

    ADIAnalogInNode(NodeManager* node_manager, pros::ext_adi_port_pair_t port_pair, std::string handle_name, bool reverse=false);

    void initialize();

    int getValue();

    void teleopPeriodic();

    void autonPeriodic();

    ~ADIAnalogInNode();
};
