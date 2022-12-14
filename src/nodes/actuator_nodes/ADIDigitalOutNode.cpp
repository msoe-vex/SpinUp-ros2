#include "nodes/actuator_nodes/ADIDigitalOutNode.h"

ADIDigitalOutNode::ADIDigitalOutNode(NodeManager* node_manager, std::string handle_name,
    int port, bool initial_state, bool reverse) : Node(node_manager, 10), 
    m_digital_out(port, initial_state),
    m_reverse(reverse) {
    m_handle_name = handle_name.insert(0, "output/");
}

ADIDigitalOutNode::ADIDigitalOutNode(NodeManager* node_manager, std::string handle_name,
    pros::ext_adi_port_pair_t port_pair, bool initial_state, bool reverse) : Node(node_manager, 10), 
    m_digital_out(port_pair, initial_state),
    m_reverse(reverse) {
    m_handle_name = handle_name.insert(0, "output/");
}

void ADIDigitalOutNode::initialize() {
}

void ADIDigitalOutNode::setValue(bool value) {
    m_digital_out.set_value(m_reverse ? !value : value);
}

ADIDigitalOutNode::~ADIDigitalOutNode() {
}