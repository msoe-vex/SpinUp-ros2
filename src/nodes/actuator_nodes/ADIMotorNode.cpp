#include "lib-rr/nodes/actuator_nodes/ADIMotorNode.h"

ADIMotorNode::ADIMotorNode(NodeManager* node_manager, std::string handle_name,
    int port) : Node(node_manager, 50), 
    m_motor(port) {
    m_handle_name = handle_name.insert(0, "output/");
    m_sub_motor_name = m_handle_name + "/adiMotor";
    m_motor_sub = new ros::Subscriber<std_msgs::Int16, ADIMotorNode>
        (m_sub_motor_name.c_str(), &ADIMotorNode::m_setValue, this);
}

ADIMotorNode::ADIMotorNode(NodeManager* node_manager, std::string handle_name,
    pros::ext_adi_port_pair_t port_pair) : Node(node_manager, 50), 
    m_motor(port_pair) {
    m_handle_name = handle_name.insert(0, "output/");
    m_sub_motor_name = m_handle_name + "/adiMotor";
    m_motor_sub = new ros::Subscriber<std_msgs::Int16, ADIMotorNode>
        (m_sub_motor_name.c_str(), &ADIMotorNode::m_setValue, this);
}


void ADIMotorNode::m_setValue(const std_msgs::Int16& msg) {
    m_motor.set_value(msg.data);
}

void ADIMotorNode::setValue(const int speed) {
    m_motor.set_value(speed);
}

void ADIMotorNode::initialize() {
    Node::m_handle->initNode();
    Node::m_handle->subscribe(*m_motor_sub);
}

ADIMotorNode::~ADIMotorNode() {
    delete m_motor_sub;
}