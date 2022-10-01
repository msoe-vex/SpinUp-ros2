#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "api.h"
#include "ros_lib/ros.h"
#include "ros_lib/std_msgs/Int16.h"
#include "ros_lib/std_msgs/Empty.h"

class ADIUltrasonicNode : public Node {
private:
    pros::ADIUltrasonic m_ultrasonic;
    std_msgs::Int16 m_ultrasonic_msg;
    std::string m_handle_name;
    std::string m_sub_publish_data_name;
    ros::Publisher* m_publisher;
    ros::Subscriber<std_msgs::Empty, ADIUltrasonicNode>* m_publish_data_sub;

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
