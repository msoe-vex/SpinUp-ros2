#include "nodes/sensor_nodes/ADIDigitalInNode.h"

// By default, this constructor calls the constructor for the Node object in
// NodeManager.h
ADIDigitalInNode::ADIDigitalInNode(NodeManager* node_manager, int port,
    std::string handle_name) : Node(node_manager, 10),
     m_digital_in(port) {
    m_handle_name = handle_name.insert(0, "sensor/");
}

ADIDigitalInNode::ADIDigitalInNode(NodeManager* node_manager, pros::ext_adi_port_pair_t port_pair,
    std::string handle_name) : Node(node_manager, 10), m_digital_in(port_pair) {
    m_handle_name = handle_name.insert(0, "sensor/");
}

void ADIDigitalInNode::initialize() {
}

int ADIDigitalInNode::getValue() {
    return m_digital_in.get_value();
}

void ADIDigitalInNode::teleopPeriodic() {

}

void ADIDigitalInNode::autonPeriodic() {
    
}

ADIDigitalInNode::~ADIDigitalInNode() { 
 }