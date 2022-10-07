#include "lib-rr/nodes/actuator_nodes/ADIDigitalOutNode.h"

ADIDigitalOutNode::ADIDigitalOutNode(NodeManager* node_manager, std::string handle_name,
    int port, bool initial_state, bool reverse) : Node(node_manager, 10), 
    m_digital_out(port, initial_state),
    m_reverse(reverse) {
    m_handle_name = handle_name.insert(0, "output/");
    m_sub_digital_out_name = m_handle_name + "/digitalOut";

    m_digital_out_sub = new ros::Subscriber<std_msgs::Bool, ADIDigitalOutNode>
        (m_sub_digital_out_name.c_str(), &ADIDigitalOutNode::m_setValue, this);
}

ADIDigitalOutNode::ADIDigitalOutNode(NodeManager* node_manager, std::string handle_name,
    pros::ext_adi_port_pair_t port_pair, bool initial_state, bool reverse) : Node(node_manager, 10), 
    m_digital_out(port_pair, initial_state),
    m_reverse(reverse) {
    m_handle_name = handle_name.insert(0, "output/");
    m_sub_digital_out_name = m_handle_name + "/digitalOut";

    m_digital_out_sub = new ros::Subscriber<std_msgs::Bool, ADIDigitalOutNode>
        (m_sub_digital_out_name.c_str(), &ADIDigitalOutNode::m_setValue, this);
}

void ADIDigitalOutNode::m_setValue(const std_msgs::Bool& msg) {
    setValue((int)msg.data);
}

void ADIDigitalOutNode::setValue(bool value) {
    m_digital_out.set_value(m_reverse ? !value : value);
}

void ADIDigitalOutNode::initialize() {
    Node::m_handle->subscribe(*m_digital_out_sub);
}

ADIDigitalOutNode::~ADIDigitalOutNode() {
    delete m_digital_out_sub;
}