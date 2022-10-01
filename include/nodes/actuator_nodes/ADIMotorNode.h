#pragma once

#include "api.h"
#include "lib-rr/nodes/NodeManager.h"
#include "ros_lib/ros.h"
#include "ros_lib/std_msgs/Int16.h"

class ADIMotorNode : public Node {

private:
    pros::ADIMotor m_motor;
    std::string m_handle_name;
    std::string m_sub_motor_name;
    ros::Subscriber<std_msgs::Int16, ADIMotorNode>* m_motor_sub;

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