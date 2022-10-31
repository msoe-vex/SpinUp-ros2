#include "nodes/subsystems/FlyWheelNode.h"
#include "pros/misc.h"




FlyWheelNode::FlyWheelNode(NodeManager* node_manager, std::string handle_name, ControllerNode* controller,
        MotorNode motor) : Node(node_manager, 10), 
        m_controller(controller->getController()) {
        
    PID pid(0,0,0,0);
    toggle = false;
    m_handle_name = handle_name.insert(0, "robot/");
}

void FlyWheelNode::initialize() {

}

void FlyWheelNode::teleopPeriodicA() {
    int right = (static_cast<float>(m_controller->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) / 127.0) * 50;

    motor->moveVelocity(pid->calculate(right - motor->getVelocity()));

}

void FlyWheelNode::teleopPeriodicB() {
    if (m_controller->get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
        toggle = !toggle;
    }
    if (toggle) {
        motor->moveVelocity(pid->calculate(40.0 - motor->getVelocity()));
    }
}


void FlyWheelNode::autonPeriodic() {
    
}

FlyWheelNode::~FlyWheelNode() {

}

