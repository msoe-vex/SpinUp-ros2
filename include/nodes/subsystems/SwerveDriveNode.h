#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "lib-rr/eigen/Eigen/Dense"
#include "lib-rr/swerve/SwerveController.h"
#include "lib-rr/nodes/actuator_nodes/MotorNode.h"
#include "lib-rr/nodes/sensor_nodes/ADIAnalogInNode.h"
#include "lib-rr/nodes/sensor_nodes/ControllerNode.h"
#include "lib-rr/nodes/sensor_nodes/InertialSensorNode.h"
#include "ros_lib/v5_hal/RollPitchYaw.h"

class DriverControlNode : public Node {
private:
    SwerveController swerveController;

    std::string m_handle_name;
    ros::Publisher* m_publisher;

    Eigen::Vector2d controller_target_velocity;
    Eigen::Vector2d field_target_velocity;
    Eigen::Rotation2Dd robot_angle = Eigen::Rotation2Dd(0);
    double rotation_velocity;
    double kP = 0.7;
    double kI = 0.0;
    double kD = 0.0;
    Eigen::Vector2d left_module_location;
    Eigen::Vector2d right_module_location;
    Eigen::Vector2d rear_module_location;

    MotorNode* left_swerve_1;
    MotorNode* left_swerve_2;
    MotorNode* right_swerve_1;
    MotorNode* right_swerve_2;
    MotorNode* rear_swerve_1;
    MotorNode* rear_swerve_2;
    ADIAnalogInNode* left_swerve_pot;
    ADIAnalogInNode* right_swerve_pot;
    ADIAnalogInNode* rear_swerve_pot;
    InertialSensorNode* inertial_sensor;
    pros::Controller* controller_primary;

    void m_navxDataCallback(const v5_hal::RollPitchYaw& msg);

    void m_spinIntakesVoltage(int voltage);

    void m_spinMainRollersVoltage(int voltage);

    void m_spinBottomRollersVoltage(int voltage);

    void m_spinTopRollersVoltage(int voltage);

    void m_spinEjectionRollerVoltage(int voltage);

public:
    DriverControlNode(NodeManager* node_manager, MotorNode* left_swerve_1, MotorNode* left_swerve_2, 
        ADIAnalogInNode* left_swerve_pot, MotorNode* right_swerve_1, MotorNode* right_swerve_2, 
        ADIAnalogInNode* right_swerve_pot, MotorNode* rear_swerve_1, MotorNode* rear_swerve_2, 
        ADIAnalogInNode* rear_swerve_pot, InertialSensorNode* inertial_sensor, ControllerNode* controller_primary);

    void initialize();

    void assignActualAngle(const float left_msg, const float right_msg, const float rear_msg);

    MotorPowers calculateLeftModule(Eigen::Vector2d target_velocity, double rotation_velocity);

    MotorPowers calculateRightModule(Eigen::Vector2d target_velocity, double rotation_velocity);

    MotorPowers calculateRearModule(Eigen::Vector2d target_velocity, double rotation_velocity);

    void teleopPeriodic();

    void autonPeriodic();

    ~DriverControlNode();
};
