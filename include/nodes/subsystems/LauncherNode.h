#pragma once

#include "nodes/NodeManager.h"
#include "nodes/subsystems/IClawNode.h"
#include "nodes/sensor_nodes/ControllerNode.h"
#include "nodes/actuator_nodes/ADIDigitalOutNode.h"
#include "pros/misc.h"

class LauncherNode : public IClawNode {
private:
    ControllerNode* m_controller;
    ADIDigitalOutNode* m_down_state;
    ADIDigitalOutNode* m_up_state;
    bool m_open = false;
    bool m_manual_previous_state = false;
    pros::controller_digital_e_t m_manual_button;
    pros::controller_digital_e_t m_automatic_button;

public:
    LauncherNode(NodeManager* node_manager, std::string handle_name, 
    ControllerNode* controller, ADIDigitalOutNode* down_state, ADIDigitalOutNode* up_state,
    pros::controller_digital_e_t manual_button, pros::controller_digital_e_t automatic_button);

    void initialize();

    void setState(bool up);

    void teleopPeriodic();

    void autonPeriodic();

    ~LauncherNode();
};