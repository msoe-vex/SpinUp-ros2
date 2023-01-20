#include "nodes/subsystems/ShooterNode.h"
#include "util/Constants.h"

ShooterNode::ShooterNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller, 
pros::controller_digital_e_t shoot_button, 
        MotorNode* shooter, MotorNode* shooter2) : Node(node_manager, 10), 
        m_controller(controller->getController()),
        m_shooter(shooter),
        m_shooter2(shooter2),
        m_state(IDLE),
        m_shootButton(shoot_button),
        m_PID(5,0,0,0) {
    m_handle_name = handle_name.insert(0, "robot/");
    m_target_velocity = SHOOTING_VELOCITY;
}

void ShooterNode::setTargetVelocity(double velocity) {
    m_target_velocity = velocity;
}

void ShooterNode::setState(ShooterNode::ShooterState state) {
    m_state = state;
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
            m_target_velocity = IDLE_VELOCITY;
            // if(m_currentError <= ACCEPTED_ERROR){
                
            // }

            if (shootButtonCurrentState && !m_previousShooterState) {
                m_state = SHOOTING;
            }

            break;
        case SHOOTING:
            m_target_velocity = SHOOTING_VELOCITY;

            if (shootButtonCurrentState && !m_previousShooterState) {
                m_state = IDLE;
            }

            break;
        case MANUAL:
            break;
        default:
            break;
    };

    //setShootVelocity(40.0f);
    setShooterPID();
    m_previousShooterState = shootButtonCurrentState;
}

void ShooterNode::setShooterPID() {
    m_currentError = m_target_velocity - m_shooter->getVelocity();

    m_feedback =  m_PID.calculate(m_currentError) * MAX_VELOCITY;


    pros::lcd::print(1,"Current Velocity: %f", m_shooter->getVelocity());
    m_shooter->moveVelocity(m_feedback);
    m_shooter2->moveVelocity(m_feedback);
                
}

void ShooterNode::autonPeriodic() {
    
}

ShooterNode::~ShooterNode() {
    delete m_shooter;
}