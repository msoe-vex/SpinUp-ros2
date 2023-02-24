#pragma once

#include "nodes/NodeManager.h"
#include "api.h"
#include "nodes/actuator_nodes/MotorNode.h"
#include "nodes/sensor_nodes/ControllerNode.h"
#include "nodes/actuator_nodes/ADIDigitalOutNode.h"
#include "nodes/subsystems/IRollerIntakeNode.h"
#include "util/Constants.h"

class IntakeNode : public IRollerIntakeNode {
public:
    enum IntakeState {
        INTAKING, OUTTAKING, HOLDING
    };

    IntakeNode(NodeManager* node_manager, std::string handle_name, 
    ControllerNode* controller, pros::controller_digital_e_t intake_button, 
    pros::controller_digital_e_t outtake_button, std::vector<MotorNode*> intakes);

    void setIntakeVoltage(int voltage);

    void setIntakeVelocity(float velocity);

    void initialize();

    void teleopPeriodic();

    void autonPeriodic();

    ~IntakeNode();

private:
    IntakeState m_state;

    pros::Controller* m_controller;
    std::vector<MotorNode*> m_intakes;

    pros::controller_digital_e_t m_intakeButton;
    pros::controller_digital_e_t m_outtakeButton;

    bool m_previousIntakeState = false;

    std::string m_handle_name;
};
