#pragma once

#include "nodes/NodeManager.h"
#include "api.h"
#include "nodes/actuator_nodes/MotorNode.h"
#include "nodes/sensor_nodes/ControllerNode.h"
#include "nodes/actuator_nodes/ADIDigitalOutNode.h"
#include "nodes/subsystems/IShooterNode.h"
#include "util/Constants.h"

class ShooterNode: public IShooterNode {
public:
    enum ShooterState {
        SHOOTING, REVERSE, IDLE
    };

    ShooterNode(NodeManager* node_manager, std::string handle_name, 
    ControllerNode* controller, pros::controller_digital_e_t shoot_button, 
    pros::controller_digital_e_t reverse_button, MotorNode* shooter, MotorNode* shooter2);

    void setShootVoltage(int voltage);

    void setShootVelocity(float velocity);

    void initialize();

    void teleopPeriodic();

    void autonPeriodic();

    ~ShooterNode();

private:
    ShooterState m_state;

    pros::Controller* m_controller;
    MotorNode* m_shooter;
    MotorNode* m_shooter2;

    pros::controller_digital_e_t m_shootButton;
    pros::controller_digital_e_t m_reverseButton;

    bool m_previousShooterState = false;

    std::string m_handle_name;
};
