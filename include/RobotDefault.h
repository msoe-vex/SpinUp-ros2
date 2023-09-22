#pragma once

#include "IRobot.h"

class RobotDefault : public IRobot {
public:
    /* Node Manager */
    NodeManager *node_manager;

    /* Tank Drive Subsystem */
    MotorNode *left_drive_1;
    MotorNode *left_drive_2;
    MotorNode *left_drive_3;
    MotorNode *left_drive_4;
    MotorNode *right_drive_1;
    MotorNode *right_drive_2;
    MotorNode *right_drive_3;
    MotorNode *right_drive_4;
    TankDriveKinematics *tank_kinematics;
    TankDriveNode *tank_drive_node;

    /* Everything is an intake because we are so good at planning :) */

    MotorNode *intake_motor;
    IntakeNode* intake_node;

    MotorNode *indexer_motor;
    IntakeNode *indexer_node;
    
    MotorNode *roller_motor;
    IntakeNode *roller_node;

    void initialize() override;
    void disabled() override;
    void competition_initialize() override;
    void autonomous() override;
    void opcontrol() override;
};
