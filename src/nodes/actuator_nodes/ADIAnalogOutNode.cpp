#include "nodes/actuator_nodes/ADIAnalogOutNode.h"

ADIAnalogOutNode::ADIAnalogOutNode(NodeManager* node_manager, std::string handle_name,
    int port) : Node(node_manager, 50), 
    m_analog_out(port) {
    m_handle_name = handle_name.insert(0, "output/");
    }

ADIAnalogOutNode::ADIAnalogOutNode(NodeManager* node_manager, std::string handle_name,
    pros::ext_adi_port_pair_t port_pair) : Node(node_manager, 50), 
    m_analog_out(port_pair) {
    m_handle_name = handle_name.insert(0, "output/");
}

void ADIAnalogOutNode::setValue(int value) {
    m_analog_out.set_value(value);
}

void ADIAnalogOutNode::initialize() {
}

ADIAnalogOutNode::~ADIAnalogOutNode() {
}