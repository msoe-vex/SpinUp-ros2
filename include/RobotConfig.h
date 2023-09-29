#pragma once

#include "IRobot.h"
#include <json/value.h>

class RobotConfig : public IRobot {
public:
    /* Node Manager */
    NodeManager *node_manager;

    /* Tank Drive Subsystem */
    std::vector<MotorNode*> tank_motors;
    TankDriveKinematics *tank_kinematics;
    TankDriveNode *tank_drive_node;

    /* Everything is an intake because we are so good at planning :) */

    std::vector<MotorNode*> motors;
    std::vector<IntakeNode*> nodes;

    void initialize() override;
    void disabled() override;
    void competition_initialize() override;
    void autonomous() override;
    void opcontrol() override;

private:

};
