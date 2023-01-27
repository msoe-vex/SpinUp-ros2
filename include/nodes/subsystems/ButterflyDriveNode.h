#pragma once

#include "api.h"
#include "eigen/Eigen/Dense"
#include "kinematics/HolonomicDriveKinematics.h"
#include "kinematics/IDriveKinematics.h"
#include "kinematics/TankDriveKinematics.h"
#include "nodes/NodeManager.h"
#include "nodes/actuator_nodes/MotorNode.h"
#include "nodes/sensor_nodes/ControllerNode.h"
#include "nodes/sensor_nodes/InertialSensorNode.h"
#include "nodes/subsystems/IDriveNode.h"
#include <algorithm>
#include <initializer_list>

enum DriveMode { Tank, Holonomic };

class ButterflyDriveNode : public IDriveNode {
public:
  struct ButterflyEightMotors {
    MotorNode *left_front_motor;
    MotorNode *left_front_motor_2;
    MotorNode *left_rear_motor;
    MotorNode *left_rear_motor_2;
    MotorNode *right_front_motor;
    MotorNode *right_front_motor_2;
    MotorNode *right_rear_motor;
    MotorNode *right_rear_motor_2;
  };

  ButterflyDriveNode(NodeManager *node_manager, std::string handle_name,
                     ControllerNode *controller,
                     InertialSensorNode *inertial_sensor,
                     ButterflyEightMotors motors,
                     HolonomicDriveKinematics holo_kinematics,
                     TankDriveKinematics tank_kinematics);

  void initialize();

  void resetEncoders();

  IDriveNode::FourMotorDriveEncoderVals getIntegratedEncoderVals();

  void setDriveVoltage(int x_voltage, int theta_voltage);

  void setDriveVoltage(int x_voltage, int y_voltage, int theta_voltage);

  void setDriveVoltage(int left_x, int left_y, int right_x, int right_y);

  void setDriveVelocity(float x_velocity, float theta_velocity);

  void setDriveVelocity(float x_velocity, float y_velocity,
                        float theta_velocity);

  void teleopPeriodic();

  void autonPeriodic();

  void m_fieldOrientedControl();

  ~ButterflyDriveNode();

private:
  pros::Controller *m_controller;

  InertialSensorNode *m_inertial_sensor;

  std::string m_handle_name;

  DriveMode m_drive_mode;

  ButterflyEightMotors m_motors;

  HolonomicDriveKinematics m_holo_kinematics;
  TankDriveKinematics m_tank_kinematics;

  Eigen::Vector2d controller_target_velocity;
  Eigen::Vector2d field_target_velocity;
  double rotation_velocity;

  IDriveKinematics & m_getCurrentDriveKinematics();

  void m_setLeftFrontVoltage(int voltage);

  void m_setLeftRearVoltage(int voltage);

  void m_setRightFrontVoltage(int voltage);

  void m_setRightRearVoltage(int voltage);

  void m_setLeftFrontVelocity(float velocity);

  void m_setLeftRearVelocity(float velocity);

  void m_setRightFrontVelocity(float velocity);

  void m_setRightRearVelocity(float velocity);

  void m_tankControl();
};
