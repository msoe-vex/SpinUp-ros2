#include "nodes/subsystems/ShooterNode.h"

ShooterNode::ShooterNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller, 
pros::controller_digital_e_t shoot_button, 
        MotorNode* shooter, MotorNode* shooter2) : Node(node_manager, 10), 
        m_controller(controller->getController()),
        m_shooter(shooter),
        m_shooter2(shooter2),
        m_state(IDLE),
        m_shootButton(shoot_button) {
    m_handle_name = handle_name.insert(0, "robot/");
}

void ShooterNode::setShootVoltage(int voltage) {
    m_shooter->moveVoltage(voltage);
    m_shooter2->moveVoltage(voltage);
}

void ShooterNode::setShootVelocity(float velocity) {
    m_shooter->moveVelocity(velocity);
    m_shooter2->moveVelocity(velocity);
}

void ShooterNode::initialize() {

}

void ShooterNode::teleopPeriodic() {
    bool shootButtonCurrentState = m_controller->get_digital(m_shootButton);

    switch (m_state) {
        case IDLE:
            setShootVoltage(0);

            if (shootButtonCurrentState && !m_previousShooterState) {
                m_state = SHOOTING;
            }

            break;
        case SHOOTING:
            setShootVoltage(MAX_MOTOR_VOLTAGE);

            if (shootButtonCurrentState && !m_previousShooterState) {
                m_state = IDLE;
            }

            break;
        default:
            break;
    };

    m_previousShooterState = shootButtonCurrentState;
}

void ShooterNode::autonPeriodic() {
    
}

ShooterNode::~ShooterNode() {
    delete m_shooter;
}