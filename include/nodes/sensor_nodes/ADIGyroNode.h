#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "api.h"
#include "ros_lib/ros.h"
#include "ros_lib/std_msgs/Float32.h"
#include "ros_lib/std_msgs/Empty.h"

class ADIGyroNode : public Node {
private:
    pros::ADIGyro m_gyro;
    std_msgs::Float32 m_gyro_msg;
    std::string m_handle_name;
    std::string m_sub_publish_data_name;
    ros::Publisher* m_publisher;
    ros::Subscriber<std_msgs::Empty, ADIGyroNode>* m_publish_data_sub;

    void m_populateMessage();

    void m_publishData(const std_msgs::Empty& msg);

public:
    ADIGyroNode(NodeManager* node_manager, int port, double multiplier, std::string handle_name);

    ADIGyroNode(NodeManager* node_manager, pros::ext_adi_port_pair_t port_pair, double multiplier, std::string handle_name);

    void initialize();

    float getValue();

    void teleopPeriodic();

    void autonPeriodic();

    ~ADIGyroNode();
};
