#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "api.h"
#include "ros_lib/ros.h"
#include "ros_lib/v5_hal/CompetitionStatus.h"
#include "pros/misc.h"
#include "ros_lib/std_msgs/Empty.h"

class CompetitionStatusNode : public Node {
private: 
    v5_hal::CompetitionStatus m_comp_status_msg;
    std::string m_handle_name;
    std::string m_sub_publish_data_name;
    ros::Publisher* m_publisher;
    ros::Subscriber<std_msgs::Empty, CompetitionStatusNode>* m_publish_data_sub;

    void m_populateMessage();

    void m_publishData(const std_msgs::Empty& msg);

public:
    CompetitionStatusNode(NodeManager* node_manager, std::string handle_name);

    void initialize();

    void teleopPeriodic();

    void autonPeriodic();

    ~CompetitionStatusNode();
};