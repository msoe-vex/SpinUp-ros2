#include "nodes/sensor_nodes/ADIUltrasonicNode.h"

// By default, this constructor calls the constructor for the Node object in
// NodeManager.h
ADIUltrasonicNode::ADIUltrasonicNode(NodeManager* node_manager, int port_ping,
    int port_echo, std::string handle_name) : Node(node_manager, 10),
    m_ultrasonic(port_ping, port_echo) {
    m_handle_name = handle_name.insert(0, "sensor/");
}

ADIUltrasonicNode::ADIUltrasonicNode(NodeManager* node_manager, pros::ext_adi_port_tuple_t port_tuple,
     std::string handle_name) : Node(node_manager, 10),
    m_ultrasonic(port_tuple) {
    m_handle_name = handle_name.insert(0, "sensor/");
}

void ADIUltrasonicNode::initialize() {
}

int ADIUltrasonicNode::getValue() {
    return m_ultrasonic.get_value();
}

void ADIUltrasonicNode::teleopPeriodic() {
    
}

void ADIUltrasonicNode::autonPeriodic() {
    
}

ADIUltrasonicNode::~ADIUltrasonicNode() { 
}