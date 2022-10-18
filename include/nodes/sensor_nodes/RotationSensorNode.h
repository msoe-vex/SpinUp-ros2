#pragma once

#include "nodes/NodeManager.h"
#include "api.h"

class RotationSensorNode : public Node {
private:
    pros::Rotation m_rotation_sensor;
    std::string m_sub_publish_data_name;
    std::string m_handle_name;

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