#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "api.h"
#include "ros_lib/ros.h"
#include "ros_lib/v5_hal/V5RotationSensor.h"
#include "ros_lib/std_msgs/Empty.h"

class RotationSensorNode : public Node {
private:
    pros::Rotation m_rotation_sensor;
    v5_hal::V5RotationSensor m_rotation_msg;
    std::string m_sub_publish_data_name;
    std::string m_handle_name;
    ros::Publisher* m_publisher;
    ros::Subscriber<std_msgs::Empty, RotationSensorNode>* m_publish_data_sub;

    void m_populateMessage();

    void m_publishData(const std_msgs::Empty& msg);

public:
    RotationSensorNode(NodeManager* node_manager, int rotation_port, 
        std::string handle_name);
    
    void initialize();

    int getAngle();

    int getPosition();

    int getVelocity();
    
    void teleopPeriodic();

    void autonPeriodic();
    
    ~RotationSensorNode();
};