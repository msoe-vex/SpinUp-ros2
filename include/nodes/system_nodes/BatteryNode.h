#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "api.h"
#include "ros_lib/ros.h"
#include "ros_lib/v5_hal/V5Battery.h"
#include "ros_lib/std_msgs/Empty.h"

class BatteryNode : public Node {
private:
    v5_hal::V5Battery m_battery_msg;
    std::string m_handle_name;
    std::string m_sub_publish_data_name;
    ros::Publisher* m_publisher;
    ros::Subscriber<std_msgs::Empty, BatteryNode>* m_publish_data_sub;

    void m_populateMessage();

    void m_publishData(const std_msgs::Empty& msg);

public:
    BatteryNode(NodeManager* node_manager, std::string handle_name);

    void initialize();

    void teleopPeriodic();

    void autonPeriodic();

    ~BatteryNode();
};