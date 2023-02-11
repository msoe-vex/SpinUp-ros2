#include "nodes/sensor_nodes/ADIEncoderNode.h"

// By default, this constructor calls the constructor for the Node object in
// NodeManager.h
ADIEncoderNode::ADIEncoderNode(NodeManager* node_manager, int port_top,
    int port_bottom, std::string handle_name, bool reverse) : Node(node_manager, 10), 
    m_encoder(port_top, port_bottom, reverse) {
    m_handle_name = handle_name.insert(0, "sensor/");
}

ADIEncoderNode::ADIEncoderNode(NodeManager* node_manager, pros::ext_adi_port_tuple_t port_tuple, 
    std::string handle_name, bool reverse) : Node(node_manager, 10), 
    m_encoder(port_tuple, reverse) {
    m_handle_name = handle_name.insert(0, "sensor/");
}

void ADIEncoderNode::initialize() {
}

int ADIEncoderNode::getValue() {
    return m_encoder.get_value();
}

void ADIEncoderNode::teleopPeriodic() {
    // std::string msg = m_handle_name + " value: " + std::to_string(getValue());
    // pros::lcd::print(0, msg.c_str());
    // m_handle->logwarn(msg.c_str());
}

void ADIEncoderNode::autonPeriodic() {
    
}

ADIEncoderNode::~ADIEncoderNode() { 
}