#include "lib-rr/nodes/sensor_nodes/ADIAnalogInNode.h"

// By default, this constructor calls the constructor for the Node object in
// NodeManager.h
ADIAnalogInNode::ADIAnalogInNode(NodeManager* node_manager, int port,
    std::string handle_name, bool reverse) : Node(node_manager, 10), 
    m_analog_in(port), m_is_reversed(reverse) {
    m_handle_name = handle_name.insert(0, "sensor/");
    m_sub_publish_data_name = m_handle_name + "/publish";

    m_publisher = new ros::Publisher(m_handle_name.c_str(), &m_analog_in_msg);

    m_publish_data_sub = new ros::Subscriber<std_msgs::Empty, ADIAnalogInNode>
        (m_sub_publish_data_name.c_str(), &ADIAnalogInNode::m_publishData, this);
}

ADIAnalogInNode::ADIAnalogInNode(NodeManager* node_manager, pros::ext_adi_port_pair_t port_pair,
    std::string handle_name, bool reverse) : Node(node_manager, 10), 
    m_analog_in(port_pair), m_is_reversed(reverse) {
    m_handle_name = handle_name.insert(0, "sensor/");
    m_sub_publish_data_name = m_handle_name + "/publish";

    m_publisher = new ros::Publisher(m_handle_name.c_str(), &m_analog_in_msg);

    m_publish_data_sub = new ros::Subscriber<std_msgs::Empty, ADIAnalogInNode>
        (m_sub_publish_data_name.c_str(), &ADIAnalogInNode::m_publishData, this);
}

void ADIAnalogInNode::m_publishData(const std_msgs::Empty& msg) {
    m_populateMessage();
    m_publisher->publish(&m_analog_in_msg);
}

void ADIAnalogInNode::initialize() {
    // Initialize the handler, and set up data to publish
    Node::m_handle->advertise(*m_publisher);
}

int ADIAnalogInNode::getValue() {
    return m_analog_in.get_value();
}

void ADIAnalogInNode::teleopPeriodic() {
    
}

void ADIAnalogInNode::autonPeriodic() {

}

void ADIAnalogInNode::m_populateMessage() {
    if (m_is_reversed) {
        m_analog_in_msg.data = (4096 - m_analog_in.get_value());
    } else {
        m_analog_in_msg.data = m_analog_in.get_value();
    }
}

ADIAnalogInNode::~ADIAnalogInNode() { 
    delete m_publisher; 
}