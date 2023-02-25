#pragma once

#include "nodes/NodeManager.h"

class RollerNode : public Node {
private:
    NodeManager* m_node_manager;
    std::string m_handle_name;

    pros::Controller* m_controller;
    std::vector<MotorNode*> m_intakes;

    pros::controller_digital_e_t m_intakeButton;
    pros::controller_digital_e_t m_outtakeButton;

public:
    RollerNode(NodeManager* node_manager, std::string handle_name): Node(node_manager, 10), m_node_manager(node_manager), m_handle_name(handle_name) {};

    virtual void initialize() = 0;

    virtual void teleopPeriodic() {};

    virtual void autonPeriodic() {};

    virtual ~RollerNode() {};
};
