#pragma once

#include "nodes/NodeManager.h"
#include "nodes/sensor_nodes/ControllerNode.h"
#include "nodes/actuator_nodes/ADIDigitalOutNode.h"
#include "util/Timer.h"
#include "nodes/subsystems/ClawNode.h"
#include "pros/misc.h"

class BackClawNode : public Node {
public:
    enum BackClawState {
        PIVOT_BACK, PIVOT_DOWN_CLAW_OPEN, PIVOT_DOWN_CLAW_CLOSED
    };

    BackClawNode(NodeManager* node_manager, std::string handle_name,
        ControllerNode* controller, pros::controller_digital_e_t pivotButton, 
        pros::controller_digital_e_t clawButton, ADIDigitalOutNode* pivot,
        ADIDigitalOutNode* claw);

    void initialize();

    void setState(BackClawState state);

    void togglePivot();

    void toggleClaw();

    void teleopPeriodic();
    
    void autonPeriodic();

    ~BackClawNode();

private:
    BackClawState m_state;
    BackClawState m_previousState;
    Timer m_timer;

    pros::Controller* m_controller;
    pros::controller_digital_e_t m_pivotButton;
    pros::controller_digital_e_t m_clawButton;
    ADIDigitalOutNode* m_pivot;
    ADIDigitalOutNode* m_claw;

    std::string m_handle_name;

    bool m_pivotButtonPreivousState = false;
    bool m_clawButtonPreviousState = false;
    bool m_stateChange = false;

    void periodic();
};
