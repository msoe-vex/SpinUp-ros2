#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "api.h"
#include "ros_lib/ros.h"
#include "ros_lib/std_msgs/Bool.h"
#include "ros_lib/std_msgs/Empty.h"

class ADIDigitalInNode : public Node {
private:
    pros::ADIDigitalIn m_digital_in;
    std_msgs::Bool m_digital_in_msg;
    std::string m_handle_name;
    std::string m_sub_publish_data_name;
    ros::Publisher* m_publisher;
    ros::Subscriber<std_msgs::Empty, ADIDigitalInNode>* m_publish_data_sub;

    void m_populateMessage();

    void m_publishData(const std_msgs::Empty& msg);

public:
    ADIDigitalInNode(NodeManager* node_manager, int port, std::string handle_name);

    ADIDigitalInNode(NodeManager* node_manager, pros::ext_adi_port_pair_t port_pair, std::string handle_name);

    void initialize();

    int getValue();

    void teleopPeriodic();

    void autonPeriodic();

    ~ADIDigitalInNode();
};
