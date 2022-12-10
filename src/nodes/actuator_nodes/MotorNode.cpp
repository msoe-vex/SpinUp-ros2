#include "nodes/actuator_nodes/MotorNode.h"

// By default, this constructor calls the constructor for the Node object in
// NodeManager.h
MotorNode::MotorNode(NodeManager* node_manager, int port_number,
    std::string handle_name, bool reverse,
    pros::motor_gearset_e_t gearset) : Node(node_manager, 10),
    m_motor(port_number, gearset, reverse) {
    m_handle_name = handle_name.insert(0, "motor/");
}

void MotorNode::initialize() {
}

int MotorNode::m_getMaxRPM() {
    switch (m_motor.get_gearing()) {
        case pros::E_MOTOR_GEARSET_06:
            return 600;
        case pros::E_MOTOR_GEARSET_18:
            return 200;
        case pros::E_MOTOR_GEARSET_36:
            return 100;
        default:
            return 200;
    }
}

pros::Motor* MotorNode::getMotor() {
    return &m_motor;
}

void MotorNode::resetEncoder() {
    m_motor.tare_position();
}

int MotorNode::getPosition() {
    return m_motor.get_position();
}

void MotorNode::move(int value) {
    m_motor.move(value);
}

void MotorNode::moveVoltage(int voltage) {
    m_motor.move_voltage(voltage);
}

void MotorNode::moveVelocity(float velocity) {
    float rpm = (velocity / MAX_VELOCITY) * m_getMaxRPM();
    m_motor.move_velocity(rpm);
}

double MotorNode::getVelocity() {
    float rpm = m_motor.get_actual_velocity();
    return (rpm / m_getMaxRPM()) * MAX_VELOCITY;
}   

void MotorNode::moveAbsolute(double position, int max_velocity) {
    m_motor.move_absolute(position, max_velocity);
}

void MotorNode::teleopPeriodic() {
    
}

void MotorNode::autonPeriodic() {

}

MotorNode::~MotorNode() {
}