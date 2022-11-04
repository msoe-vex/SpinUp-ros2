#include "nodes/subsystems/FlyWheelNode.h"
#include "pros/misc.h"

FlyWheelNode::FlyWheelNode(NodeManager* node_manager, std::string handle_name, ControllerNode* m_controller,
        MotorNode* motorL, MotorNode* motorR) : 
    Node(node_manager, 10), 
    m_controller(m_controller->getController()),
    m_motorL(motorL),
    m_motorR(motorR) {
        
    PID m_pid(5,0,0,0);
    m_toggle = false;
    m_handle_name = handle_name.insert(0, "robot/");
}

void FlyWheelNode::initialize() {

}

void FlyWheelNode::teleopPeriodic() {
    float right = ((m_controller->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) / 127.0) * 50.0;

    m_motorL->moveVelocity(m_pid->calculate(right - m_motorL->getVelocity()));
    m_motorR->moveVelocity(m_pid->calculate(right - m_motorR->getVelocity()));

}

void FlyWheelNode::teleopPeriodicB() {
    if (m_controller->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
        m_toggle = !m_toggle;
    }
    if (m_toggle) {
        m_motorL->moveVelocity(m_pid->calculate(40.0 - m_motorL->getVelocity()));
        m_motorR->moveVelocity(m_pid->calculate(40.0 - m_motorR->getVelocity()));
    }
}


void FlyWheelNode::autonPeriodic() {
    
}

FlyWheelNode::~FlyWheelNode() {

}

