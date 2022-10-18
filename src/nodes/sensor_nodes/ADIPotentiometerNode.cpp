#include "nodes/sensor_nodes/ADIPotentiometerNode.h"

// By default, this constructor calls the constructor for the Node object in
// NodeManager.h
ADIPotentiometerNode::ADIPotentiometerNode(NodeManager* node_manager, int port,
    std::string handle_name, pros::adi_potentiometer_type_e potType) : Node(node_manager, 10), 
    m_potentiometer(port, potType) {
    m_handleName = handle_name.insert(0, "sensor/");
}

ADIPotentiometerNode::ADIPotentiometerNode(NodeManager* node_manager, pros::ext_adi_port_pair_t port_pair,
    std::string handle_name, pros::adi_potentiometer_type_e potType) : Node(node_manager, 10), 
    m_potentiometer(port_pair, potType) {
    m_handleName = handle_name.insert(0, "sensor/");
}

void ADIPotentiometerNode::initialize() {
}

int ADIPotentiometerNode::getValue() {
    return m_potentiometer.get_value();
}

double ADIPotentiometerNode::getAngle() {
    return m_potentiometer.get_angle();
}

void ADIPotentiometerNode::teleopPeriodic() {
    
}

void ADIPotentiometerNode::autonPeriodic() {

}

ADIPotentiometerNode::~ADIPotentiometerNode() { 
}