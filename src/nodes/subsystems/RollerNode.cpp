#include "nodes/subsystems/RollerNode.h"

RollerNode::RollerNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller, 
pros::controller_digital_e_t intake_button, pros::controller_digital_e_t outtake_button, 
        std::vector<MotorNode*> intakes) : Node(node_manager, handle_name), 
        m_controller(controller->getController()),
        m_intakes(intakes),
        m_state(HOLDING),
        m_intakeButton(intake_button),
        m_outtakeButton(outtake_button) {
    m_handle_name = handle_name.insert(0, "robot/");
}

void IntakeNode::setIntakeVoltage(int voltage) {
    for (auto intake : m_intakes) {
        intake->moveVoltage(voltage);
    }
}

void IntakeNode::setIntakeVelocity(float velocity) {
    for (auto intake : m_intakes) {
        intake->moveVelocity(velocity);
    }
}

void IntakeNode::initialize() {

}

void IntakeNode::teleopPeriodic() {
    bool intakeButtonCurrentState = m_controller->get_digital(m_intakeButton);
    bool outtakeButtonCurrentState = m_controller->get_digital(m_outtakeButton);

    switch (m_state) {
        case HOLDING:
            setIntakeVoltage(0);

            if (intakeButtonCurrentState && !m_previousIntakeState) {
                m_state = INTAKING;
            } else if (outtakeButtonCurrentState == 1) {
                m_state = OUTTAKING;
            }

            break;
        case INTAKING:
            setIntakeVoltage(MAX_MOTOR_VOLTAGE);

            if (intakeButtonCurrentState && !m_previousIntakeState) {
                m_state = HOLDING;
            } else if (outtakeButtonCurrentState) {
                m_state = OUTTAKING;
            }

            break;
        case OUTTAKING:
            setIntakeVoltage(-1 * MAX_MOTOR_VOLTAGE);

            if (intakeButtonCurrentState) {
                m_state = INTAKING;
            } else if (!outtakeButtonCurrentState) {
                m_state = HOLDING;
            }

            break;
        default:
            break;
    };

    m_previousIntakeState = intakeButtonCurrentState;
}

void IntakeNode::autonPeriodic() {
    
}

IntakeNode::~IntakeNode() {
    for (auto intake : m_intakes) {
        delete intake;
    }
}