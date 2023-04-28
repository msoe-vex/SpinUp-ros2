#pragma once

#include "HolonomicDriveNode.h"
#include "nodes/NodeManager.h"
#include "nodes/subsystems/IClawNode.h"
#include "nodes/sensor_nodes/ControllerNode.h"
#include "nodes/actuator_nodes/ADIDigitalOutNode.h"
#include "pros/misc.h"

class ButterflyNode : public IClawNode {
private:
    ControllerNode* m_controller;
    ADIDigitalOutNode* m_claw;
    bool m_claw_open = false;
    bool m_a_previous_state = false;
    pros::controller_digital_e_t m_button;
    HolonomicDriveNode* m_holonomic_drive_node;

public:
    ButterflyNode(NodeManager* node_manager, std::string handle_name, 
    ControllerNode* controller, ADIDigitalOutNode* claw, pros::controller_digital_e_t button, HolonomicDriveNode* holonomic_drive_node);

    void initialize();

    void setState(bool opened);

    void teleopPeriodic();

    void autonPeriodic();

    ~ButterflyNode();
};