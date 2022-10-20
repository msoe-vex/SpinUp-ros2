#include "nodes/actuator_nodes/ADIMotorNode.h"

ADIMotorNode::ADIMotorNode(NodeManager* node_manager, std::string handle_name,
    int port) : Node(node_manager, 50), 
    m_motor(port) {
    m_handle_name = handle_name.insert(0, "output/");
}

ADIMotorNode::ADIMotorNode(NodeManager* node_manager, std::string handle_name,
    pros::ext_adi_port_pair_t port_pair) : Node(node_manager, 50), 
    m_motor(port_pair) {
    m_handle_name = handle_name.insert(0, "output/");
}

void ADIMotorNode::initialize() {
}

void ADIMotorNode::setValue(const int speed) {
    m_motor.set_value(speed);
}

ADIMotorNode::~ADIMotorNode() {
}