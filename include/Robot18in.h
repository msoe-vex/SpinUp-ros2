#pragma once

#include "IRobot.h"

class Robot18in : public IRobot {
public:
    /* Node Manager */
    NodeManager *node_manager;

    /* Tank Drive Subsystem */
    MotorNode *left_front_drive;
    MotorNode *left_front_drive_2;
    MotorNode *left_rear_drive;
    MotorNode *left_rear_drive_2;
    MotorNode *right_front_drive;
    MotorNode *right_front_drive_2;
    MotorNode *right_rear_drive;
    MotorNode *right_rear_drive_2;
    TankDriveNode *tank_drive_node;

    /* Intake Subsystem */
    MotorNode *intake_motor;
    IntakeNode* intake_node;

    /* Indexer Subsystem */
    MotorNode *indexer_motor;
    IntakeNode *indexer_node;

    /* Encoders */
    ADIEncoderNode* encoder;

    /* Shooter Subsystem */
    MotorNode *shooter_motor;
    MotorNode *shooter_motor_2;
    ShooterNode* shooter_node;

    /* Intertial Sensor */
    InertialSensorNode *inertial_sensor;

    void initialize() override;
    void disabled() override;
    void competition_initialize() override;
    void autonomous() override;
    void opcontrol() override;
};
