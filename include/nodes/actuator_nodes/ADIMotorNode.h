#pragma once

#include "api.h"
#include "nodes/NodeManager.h"

class ADIMotorNode : public Node {

private:
    pros::ADIMotor m_motor;

    void m_setValue(const std_msgs::Int16& msg);

public:
    ADIMotorNode(NodeManager* node_manager, std::string handle_name, int port);

    ADIMotorNode(NodeManager* node_manager, std::string handle_name, pros::ext_adi_port_pair_t port_pair);

    void initialize();

    void setValue(const int speed);

    void teleopPeriodic();

    void autonPeriodic();

    ~ADIMotorNode();
};