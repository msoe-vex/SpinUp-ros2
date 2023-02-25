#pragma once

#include "IRobot.h"

class Robot15in : public IRobot {
public:
    /* Node Manager */
    NodeManager *node_manager;

    /* X-Drive Subsystem */
    MotorNode *left_front_drive;
    MotorNode *left_front_drive_2;
    MotorNode *left_rear_drive;
    MotorNode *left_rear_drive_2;
    MotorNode *right_front_drive;
    MotorNode *right_front_drive_2;
    MotorNode *right_rear_drive;
    MotorNode *right_rear_drive_2;
    HolonomicDriveKinematics *holonomic_drive_kinematics;
    HolonomicDriveNode *holonomic_drive_node;

    /* Intake Subsystem */
    MotorNode* intake_motor;
    IntakeNode* intake_node;
    
    MotorNode* intake_motor_2;
    IntakeNode* intake_node_2;

    MotorNode* intake_motor_3;
    IntakeNode* intake_node_3;

    /* Indexer Subsystem */
    MotorNode *indexer_motor;
    IntakeNode *indexer_node;

    /* Encoders */
    ADIEncoderNode* encoder;

    /* Shooter Subsystem */
    MotorNode *shooter_motor;
    MotorNode *shooter_motor_2;
    ShooterNode* shooter_node;
    
    /* Shoot Pneumatics Subsystem */
    ClawNode* shooter_piston_node;

    /* End-Game Pneumatics Subsystem*/
    ClawNode* end_game_node;

    /* Intertial Sensor */
    InertialSensorNode *inertial_sensor;

    /* Standard PROS structural functions */
    void initialize() override;
    void disabled() override;
    void competition_initialize() override;
    void autonomous() override;
    void opcontrol() override;
};
