#pragma once

#include "nodes/NodeManager.h"
#include "api.h"
#include "ros_lib/std_msgs/UInt32.h"

class ProsTimeNode : public Node {
private:
    std_msgs::UInt32 m_pros_time_msg;
    std::string m_handle_name;
    std::string m_sub_publish_data_name;
    ros::Publisher* m_publisher;
    ros::Subscriber<std_msgs::Empty, ProsTimeNode>* m_publish_data_sub;

    void m_populateMessage();

    void m_publishData(const std_msgs::Empty& msg);
    
public:
    ProsTimeNode(NodeManager* node_handle, std::string handle_name);

    void initialize();

    int getValue();
    
    void teleopPeriodic();

    void autonPeriodic();

    ~ProsTimeNode();
};