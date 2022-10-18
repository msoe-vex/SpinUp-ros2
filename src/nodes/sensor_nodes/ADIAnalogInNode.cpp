#include "nodes/sensor_nodes/ADIAnalogInNode.h"

// By default, this constructor calls the constructor for the Node object in
// NodeManager.h
ADIAnalogInNode::ADIAnalogInNode(NodeManager* node_manager, int port,
    std::string handle_name, bool reverse) : Node(node_manager, 10), 
    m_analog_in(port), m_is_reversed(reverse) {
    m_handle_name = handle_name.insert(0, "sensor/");
}

ADIAnalogInNode::ADIAnalogInNode(NodeManager* node_manager, pros::ext_adi_port_pair_t port_pair,
    std::string handle_name, bool reverse) : Node(node_manager, 10), 
    m_analog_in(port_pair), m_is_reversed(reverse) {
    m_handle_name = handle_name.insert(0, "sensor/");
}

void ADIAnalogInNode::initialize() {
}

int ADIAnalogInNode::getValue() {
    return m_analog_in.get_value();
}

void ADIAnalogInNode::teleopPeriodic() {
    
}

void ADIAnalogInNode::autonPeriodic() {

}

ADIAnalogInNode::~ADIAnalogInNode() { 
}