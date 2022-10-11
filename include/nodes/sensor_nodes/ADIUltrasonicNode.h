#pragma once

#include "nodes/NodeManager.h"
#include "api.h"

class ADIUltrasonicNode : public Node {
private:
    pros::ADIUltrasonic m_ultrasonic;
    std::string m_handle_name;

    void m_populateMessage();

    void m_publishData(const std_msgs::Empty& msg);

public:
    ADIUltrasonicNode(NodeManager* node_manager, int port_ping, int port_echo, std::string handle_name);

    ADIUltrasonicNode(NodeManager* node_manager, pros::ext_adi_port_tuple_t port_tuple, std::string handle_name);

    void initialize();

    int getValue();

    void teleopPeriodic();

    void autonPeriodic();

    ~ADIUltrasonicNode();
};
