#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "ros_lib/ros.h"
#include "lib-rr/nodes/sensor_nodes/ADIEncoderNode.h"
#include "lib-rr/nodes/sensor_nodes/InertialSensorNode.h"
#include "lib-rr/nodes/actuator_nodes/MotorNode.h"
#include "lib-rr/odometry/IOdometry.h"
#include "lib-rr/odometry/FollowerOdometry.h"
#include "lib-rr/odometry/TankOdometry.h"
#include "lib-rr/util/Encoders.h"
#include "lib-rr/eigen/Eigen/Dense"
#include "lib-rr/util/Logger.h"
#include "lib-rr/util/Timer.h"

class OdometryNode : public Node { 
public:
    enum OdomConfig {
        FOLLOWER, TANK
    };

    OdometryNode(NodeManager* node_manager, std::string handle_name, ADIEncoderNode* odom_encoder_1, 
        ADIEncoderNode* odom_encoder_2, InertialSensorNode* inertial_sensor, OdomConfig odom_config, IOdometry::EncoderLocations locations);

    OdometryNode(NodeManager* node_manager, std::string handle_name, MotorNode* motor_1, MotorNode* motor_2, 
        InertialSensorNode* inertial_sensor, OdomConfig odom_config, IOdometry::EncoderLocations locations);

    void initialize();

    void setCurrentPose(Pose pose);

    Pose getCurrentPose();

    void teleopPeriodic();

    void autonPeriodic();

    ~OdometryNode();

private:    
    std::string m_handle_name;

    OdomConfig m_odom_config;

    IOdometry::EncoderLocations m_locations;

    ADIEncoderNode* m_odom_encoder_1;
    ADIEncoderNode* m_odom_encoder_2;
    MotorNode* m_motor_1;
    MotorNode* m_motor_2;
    InertialSensorNode* m_inertial_sensor_node;
    Eigen::Rotation2Dd m_current_angle_offset;

    IOdometry* m_odom;

    Timer m_timer;
    double lastTime = 0.;
    double delayTime = 0.25;

    IOdometry* m_getOdomClass(OdomConfig odom_config);
};
