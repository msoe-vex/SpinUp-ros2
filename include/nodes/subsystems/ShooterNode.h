#pragma once

#include "nodes/NodeManager.h"
#include "api.h"
#include "math.h"
#include "nodes/actuator_nodes/MotorNode.h"
#include "nodes/sensor_nodes/ControllerNode.h"
#include "nodes/actuator_nodes/ADIDigitalOutNode.h"
#include "util/Constants.h"
#include "util/PID.h"
#include "nodes/actuator_nodes/MotorNode.h"


class ShooterNode: public Node {
public:
    enum ShooterState {
        SHOOTING, REVERSE, IDLE, TEST
    };

    ShooterNode(NodeManager* node_manager, std::string handle_name, 
    ControllerNode* controller, pros::controller_digital_e_t shoot_button, 
    MotorNode* shooter, MotorNode* shooter2);

    void setShootVoltage(int voltage);

    void setShootVelocity(float velocity);

    void initialize();

    void teleopPeriodic();

    void autonPeriodic();

    void setShooterPID();

    ~ShooterNode();

private:
    ShooterState m_state;

    pros::Controller* m_controller;
    MotorNode* m_shooter;
    MotorNode* m_shooter2;

    pros::controller_digital_e_t m_shootButton;

    bool m_previousShooterState = false;

    PID m_PID;

    float m_currentError;
    float m_target_velocity;
    float m_feedback;

    std::string m_handle_name;
};
