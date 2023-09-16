#pragma once

#include "IRobot.h"

class RobotFatAlbert : public IRobot {
public:
    /* Node Manager */
    NodeManager *node_manager;

    /* Tank Drive Subsystem */
    MotorNode *left_drive_1;
    MotorNode *left_drive_2;
    MotorNode *left_drive_3;
    MotorNode *right_drive_1;
    MotorNode *right_drive_2;
    MotorNode *right_drive_3;
    TankDriveKinematics *tank_kinematics;
    TankDriveNode *tank_drive_node;

    /* Intake Subsystem */
    // MotorNode *intake_motor;
    // IntakeNode* intake_node;

    // /* Indexer Subsystem */
    // MotorNode *indexer_motor;
    // IntakeNode *indexer_node;
    
    // /* Roller Subsystem */
    // MotorNode *roller_motor;
    // IntakeNode *roller_node;

    void initialize() override;
    void disabled() override;
    void competition_initialize() override;
    void autonomous() override;
    void opcontrol() override;
};
