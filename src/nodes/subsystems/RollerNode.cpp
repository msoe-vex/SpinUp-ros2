#include "nodes/subsystems/RollerNode.h"

RollerNode::RollerNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller, 
pros::controller_digital_e_t intake_button, pros::controller_digital_e_t outtake_button, 
        std::vector<MotorNode*> intakes) : IRollerIntakeNode(node_manager, handle_name), 
        m_controller(controller->getController()),
        m_intakes(intakes),
        m_state(HOLDING),
        m_intakeButton(intake_button),
        m_outtakeButton(outtake_button) {
    m_handle_name = handle_name.insert(0, "robot/");
}

void RollerNode::setIntakeVoltage(int voltage) {
    for (auto intake : m_intakes) {
        intake->moveVoltage(voltage);
    }
}

void RollerNode::setIntakeVelocity(float velocity) {
    for (auto intake : m_intakes) {
        intake->moveVelocity(velocity);
    }
}

void RollerNode::initialize() {

}

void RollerNode::teleopPeriodic() {
    bool intakeButtonCurrentState = m_controller->get_digital(m_intakeButton);
    bool outtakeButtonCurrentState = m_controller->get_digital(m_outtakeButton);
    
    if (intakeButtonCurrentState) {
        setIntakeVoltage(MAX_MOTOR_VOLTAGE);
    } else if (outtakeButtonCurrentState) {
        setIntakeVoltage(-1 * MAX_MOTOR_VOLTAGE);
    } else {
        setIntakeVoltage(0);
    }
}

void RollerNode::autonPeriodic() {
    
}

RollerNode::~RollerNode() {
    for (auto intake : m_intakes) {
        delete intake;
    }
}