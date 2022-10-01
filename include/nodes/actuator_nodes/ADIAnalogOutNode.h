#pragma once

#include "api.h"
#include "lib-rr/nodes/NodeManager.h"
#include "ros_lib/ros.h"
#include "ros_lib/std_msgs/Int16.h"

class ADIAnalogOutNode : public Node {

private:
    pros::ADIAnalogOut m_analog_out;
    std::string m_handle_name;
    std::string m_sub_analog_out_name;
    ros::Subscriber<std_msgs::Int16, ADIAnalogOutNode>* m_analog_out_sub;

    void m_setValue(const std_msgs::Int16& msg);

public:
    ADIAnalogOutNode(NodeManager* node_manager, std::string handle_name, int port);

    ADIAnalogOutNode(NodeManager* node_manager, std::string handle_name, pros::ext_adi_port_pair_t port_pair);

    void initialize();

    void teleopPeriodic();

    void autonPeriodic();

    ~ADIAnalogOutNode();
};