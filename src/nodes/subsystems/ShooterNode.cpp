#include "nodes/subsystems/ShooterNode.h"
#include "util/Constants.h"

ShooterNode::ShooterNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller, 
pros::controller_digital_e_t shoot_button, 
        std::vector<MotorNode*> shooters) : Node(node_manager, 10), 
        m_controller(controller->getController()),
        m_shooters(shooters),
        m_state(IDLE),
        m_shootButton(shoot_button),
        m_PID(5,0,0,0) {
    m_handle_name = handle_name.insert(0, "robot/");
    m_target_velocity = IDLE_VELOCITY;
}

void ShooterNode::setTargetVelocity(double velocity) {
    m_target_velocity = velocity;
}

void ShooterNode::setState(ShooterNode::ShooterState state) {
    m_state = state;
}

void ShooterNode::setShootVoltage(int voltage) {
    for (auto shooter : m_shooters) {
        shooter->moveVoltage(voltage);
    }
}

void ShooterNode::setShootVelocity(float velocity) {
    for (auto shooter : m_shooters) {
        shooter->moveVelocity(velocity);
    }
}

void ShooterNode::initialize() {

}

void ShooterNode::teleopPeriodic() {
    bool shootButtonCurrentState = m_controller->get_digital(m_shootButton);

    switch (m_state) {
        case IDLE:
            m_target_velocity = IDLE_VELOCITY;

            if (shootButtonCurrentState && !m_previousShooterButtonState) {
                m_state = SHOOTING;
            }

            break;
        case SHOOTING:
            m_target_velocity = SHOOTING_VELOCITY;

            if (shootButtonCurrentState && !m_previousShooterButtonState) {
                m_state = IDLE;
            }

            break;
        case MANUAL:
            //Uses set target velocity to control velocity externally
            if (m_controller->get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
                m_target_velocity++;
            } else if (m_controller->get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
                m_target_velocity--;
            }
            break;
        default:
            break;
    };

    //setShootVelocity(40.0f);
    updateShooterPID();
    m_previousShooterButtonState = shootButtonCurrentState;
}

void ShooterNode::updateShooterPID() {
    m_currentError = m_target_velocity - m_shooters.front()->getVelocity();
    m_feedback =  m_PID.calculate(m_currentError) * MAX_VELOCITY;


    pros::lcd::print(1,"Current Velocity: %f", m_shooters.front()->getVelocity());
    pros::lcd::print(2,"Target Velocity: %f", m_target_velocity);
    setShootVelocity(m_feedback);
}

void ShooterNode::autonPeriodic() {
    
}

ShooterNode::~ShooterNode() {
    for (auto shooter : m_shooters) {
        delete shooter;
    }
}