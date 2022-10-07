#include "lib-rr/nodes/sensor_nodes/ADIDigitalInNode.h"

// By default, this constructor calls the constructor for the Node object in
// NodeManager.h
ADIDigitalInNode::ADIDigitalInNode(NodeManager* node_manager, int port,
    std::string handle_name) : Node(node_manager, 10),
     m_digital_in(port) {
    m_handle_name = handle_name.insert(0, "sensor/");
    m_sub_publish_data_name = m_handle_name + "/publish";

    m_publisher = new ros::Publisher(m_handle_name.c_str(), &m_digital_in_msg);

    m_publish_data_sub = new ros::Subscriber<std_msgs::Empty, ADIDigitalInNode>
        (m_sub_publish_data_name.c_str(), &ADIDigitalInNode::m_publishData, this);
}

ADIDigitalInNode::ADIDigitalInNode(NodeManager* node_manager, pros::ext_adi_port_pair_t port_pair,
    std::string handle_name) : Node(node_manager, 10), m_digital_in(port_pair) {
    m_handle_name = handle_name.insert(0, "sensor/");
    m_sub_publish_data_name = m_handle_name + "/publish";

    m_publisher = new ros::Publisher(m_handle_name.c_str(), &m_digital_in_msg);

    m_publish_data_sub = new ros::Subscriber<std_msgs::Empty, ADIDigitalInNode>
        (m_sub_publish_data_name.c_str(), &ADIDigitalInNode::m_publishData, this);
}

void ADIDigitalInNode::m_publishData(const std_msgs::Empty& msg) {
    m_populateMessage();
    m_publisher->publish(&m_digital_in_msg);
}

void ADIDigitalInNode::initialize() {
    // Initialize the handler, and set up data to publish
    Node::m_handle->advertise(*m_publisher);
}

int ADIDigitalInNode::getValue() {
    return m_digital_in.get_value();
}

void ADIDigitalInNode::teleopPeriodic() {

}

void ADIDigitalInNode::autonPeriodic() {
    
}

void ADIDigitalInNode::m_populateMessage() {
    // By defalt, C++ maps 0 to false and 1 to true
    m_digital_in_msg.data = (bool)getValue();
}

ADIDigitalInNode::~ADIDigitalInNode() { 
    delete m_publisher;
 }