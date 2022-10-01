#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "api.h"
#include "ros_lib/ros.h"
#include "ros_lib/std_msgs/Int32.h"
#include "ros_lib/std_msgs/Empty.h"

class ADIEncoderNode : public Node {
private:
    pros::ADIEncoder m_encoder;
    std_msgs::Int32 m_encoder_msg;
    std::string m_handle_name;
    std::string m_sub_publish_data_name;
    ros::Publisher* m_publisher;
    ros::Subscriber<std_msgs::Empty, ADIEncoderNode>* m_publish_data_sub;

    void m_populateMessage();

    void m_publishData(const std_msgs::Empty& msg);

public:
    ADIEncoderNode(NodeManager* node_manager, int port_top, int port_bottom, std::string handle_name, bool reverse=false);

    ADIEncoderNode(NodeManager* node_manager, pros::ext_adi_port_tuple_t port_tuple, std::string handle_name, bool reverse=false);

    void initialize();

    int getValue();

    void teleopPeriodic();

    void autonPeriodic();

    ~ADIEncoderNode();
};
