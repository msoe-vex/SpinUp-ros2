#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "api.h"
#include "ros_lib/ros.h"
#include "ros_lib/std_msgs/Int16.h"
#include "ros_lib/std_msgs/Empty.h"

class ADIAnalogInNode : public Node {
private:
    pros::ADIAnalogIn m_analog_in;
    std_msgs::Int16 m_analog_in_msg;
    std::string m_handle_name;
    std::string m_sub_publish_data_name;
    ros::Publisher* m_publisher;
    ros::Subscriber<std_msgs::Empty, ADIAnalogInNode>* m_publish_data_sub;

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
