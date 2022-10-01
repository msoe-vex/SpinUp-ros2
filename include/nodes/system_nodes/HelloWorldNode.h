#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "api.h"
#include "ros_lib/ros.h"
#include "ros_lib/std_msgs/String.h"
#include "ros_lib/std_msgs/Empty.h"

class HelloWorldNode : public Node {
private:
    std_msgs::String m_string_msg;
    std::string m_handle_name;
    std::string m_sub_publish_data_name;
    ros::Publisher* m_publisher;
    ros::Subscriber<std_msgs::Empty, HelloWorldNode>* m_publish_data_sub;

    void m_populateMessage();

    void m_publishData(const std_msgs::Empty& msg);

public:
    HelloWorldNode(NodeManager* node_manager, std::string handle_name);

    void initialize();

    void teleopPeriodic();

    void autonPeriodic();

    ~HelloWorldNode();
};
