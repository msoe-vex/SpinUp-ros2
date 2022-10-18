#include "nodes/sensor_nodes/ADIGyroNode.h"

// By default, this constructor calls the constructor for the Node object in
// NodeManager.h
ADIGyroNode::ADIGyroNode(NodeManager* node_manager, int port, double multiplier,
    std::string handle_name) : Node(node_manager, 10), m_gyro(port, multiplier) {
    m_handle_name = handle_name.insert(0, "sensor/");
}

ADIGyroNode::ADIGyroNode(NodeManager* node_manager, pros::ext_adi_port_pair_t port_pair, 
    double multiplier, std::string handle_name) : 
    Node(node_manager, 10), m_gyro(port_pair, multiplier) {
    m_handle_name = handle_name.insert(0, "sensor/");
}

void ADIGyroNode::initialize() {
}

float ADIGyroNode::getValue() {
    return m_gyro.get_value();
}

void ADIGyroNode::teleopPeriodic() {
    
}

void ADIGyroNode::autonPeriodic() {
    
}

ADIGyroNode::~ADIGyroNode() { 
}