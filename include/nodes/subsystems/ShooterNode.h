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
        SHOOTING, IDLE, MANUAL
    };

    ShooterNode(NodeManager* node_manager, std::string handle_name, 
    ControllerNode* controller, pros::controller_digital_e_t shoot_button, 
    std::vector<MotorNode*> shooters);

    void setTargetVelocity(double velocity);

    void setState(ShooterNode::ShooterState state);

    void initialize();

    void teleopPeriodic();

    void autonPeriodic();

    ~ShooterNode();

private:

    void setShootVoltage(int voltage);

    void setShootVelocity(float velocity);

    void updateShooterPID();

    ShooterState m_state;

    pros::Controller* m_controller;
    std::vector<MotorNode*> m_shooters;

    pros::controller_digital_e_t m_shootButton;

    bool m_previousShooterButtonState = false;

    PID m_PID;

    float m_currentError;
    float m_target_velocity;
    float m_feedback;

    std::string m_handle_name;
};
