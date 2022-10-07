#include "lib-rr/nodes/actuator_nodes/MotorNode.h"

// By default, this constructor calls the constructor for the Node object in
// NodeManager.h
MotorNode::MotorNode(NodeManager* node_manager, int port_number,
    std::string handle_name, bool reverse,
    pros::motor_gearset_e_t gearset) : Node(node_manager, 10),
    m_motor(port_number, gearset, reverse) {
    m_handle_name = handle_name.insert(0, "motor/");
    m_sub_move_motor_voltage_name = m_handle_name + "/moveMotorVoltage";
    m_sub_publish_data_name = m_handle_name + "/publish";

    m_publisher = new ros::Publisher(m_handle_name.c_str(), &m_motor_msg);

    m_publish_data_sub = new ros::Subscriber<std_msgs::Empty, MotorNode>
        (m_sub_publish_data_name.c_str(), &MotorNode::m_publishData, this);
    
    m_move_motor_voltage_sub = new ros::Subscriber<std_msgs::Int8, MotorNode>
        (m_sub_move_motor_voltage_name.c_str(), &MotorNode::m_moveMotorVoltage, this);
}

void MotorNode::m_publishData(const std_msgs::Empty& msg) {
    m_populateMessage();
    m_publisher->publish(&m_motor_msg);
}

void MotorNode::m_moveMotorVoltage(const std_msgs::Int8& msg) {
    float voltage = (msg.data / 127.0) * (float) MAX_MOTOR_VOLTAGE;
    moveVoltage((int)voltage);
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

void MotorNode::initialize() {
    // Initialize the handler, and set up data to publish
    Node::m_handle->advertise(*m_publisher);
    Node::m_handle->subscribe(*m_move_motor_voltage_sub);
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

void MotorNode::moveAbsolute(double position, int max_velocity) {
    m_motor.move_absolute(position, max_velocity);
}

void MotorNode::teleopPeriodic() {

}

void MotorNode::autonPeriodic() {

}

void MotorNode::m_populateMessage() {
    m_motor_msg.direction = m_motor.get_direction();
    m_motor_msg.position = m_motor.get_position();
    m_motor_msg.velocity = m_motor.get_actual_velocity();
    m_motor_msg.voltage = m_motor.get_voltage();
}

MotorNode::~MotorNode() {
    delete m_publisher;
    delete m_publish_data_sub;
    delete m_move_motor_voltage_sub;
}