#include "lib-rr/nodes/actuator_nodes/ADIAnalogOutNode.h"

ADIAnalogOutNode::ADIAnalogOutNode(NodeManager* node_manager, std::string handle_name,
    int port) : Node(node_manager, 50), 
    m_analog_out(port) {
    m_handle_name = handle_name.insert(0, "output/");
    m_sub_analog_out_name = m_handle_name + "/analogOut";
    m_analog_out_sub = new ros::Subscriber<std_msgs::Int16, ADIAnalogOutNode>
        (m_sub_analog_out_name.c_str(), &ADIAnalogOutNode::m_setValue, this);
    }

ADIAnalogOutNode::ADIAnalogOutNode(NodeManager* node_manager, std::string handle_name,
    pros::ext_adi_port_pair_t port_pair) : Node(node_manager, 50), 
    m_analog_out(port_pair) {
    m_handle_name = handle_name.insert(0, "output/");
    m_sub_analog_out_name = m_handle_name + "/analogOut";
    m_analog_out_sub = new ros::Subscriber<std_msgs::Int16, ADIAnalogOutNode>
        (m_sub_analog_out_name.c_str(), &ADIAnalogOutNode::m_setValue, this);
    }

void ADIAnalogOutNode::m_setValue(const std_msgs::Int16& msg) {
    m_analog_out.set_value(msg.data);
}

void ADIAnalogOutNode::initialize() {
    Node::m_handle->initNode();
    Node::m_handle->subscribe(*m_analog_out_sub);
}

ADIAnalogOutNode::~ADIAnalogOutNode() {
    delete m_analog_out_sub;
}