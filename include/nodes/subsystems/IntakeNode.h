#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "api.h"
#include "lib-rr/nodes/actuator_nodes/MotorNode.h"
#include "lib-rr/nodes/sensor_nodes/ControllerNode.h"
#include "lib-rr/nodes/actuator_nodes/ADIDigitalOutNode.h"
#include "lib-rr/nodes/subsystems/IRollerIntakeNode.h"
#include "lib-rr/util/Constants.h"

class IntakeNode : public IRollerIntakeNode {
public:
    enum IntakeState {
        INTAKING, OUTTAKING, HOLDING
    };

    IntakeNode(NodeManager* node_manager, std::string handle_name, 
    ControllerNode* controller, pros::controller_digital_e_t intake_button, 
    pros::controller_digital_e_t outtake_button, MotorNode* intake);

    void setIntakeVoltage(int voltage);

    void setIntakeVelocity(float velocity);

    void initialize();

    void teleopPeriodic();

    void autonPeriodic();

    ~IntakeNode();

private:
    IntakeState m_state;

    pros::Controller* m_controller;
    MotorNode* m_intake;

    pros::controller_digital_e_t m_intakeButton;
    pros::controller_digital_e_t m_outtakeButton;

    bool m_previousIntakeState = false;

    std::string m_handle_name;
};
