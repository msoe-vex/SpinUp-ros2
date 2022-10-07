#include "lib-rr/nodes/sensor_nodes/ADIUltrasonicNode.h"

// By default, this constructor calls the constructor for the Node object in
// NodeManager.h
ADIUltrasonicNode::ADIUltrasonicNode(NodeManager* node_manager, int port_ping,
    int port_echo, std::string handle_name) : Node(node_manager, 10),
    m_ultrasonic(port_ping, port_echo) {
    m_handle_name = handle_name.insert(0, "sensor/");
    m_sub_publish_data_name = m_handle_name + "/publish";

    m_publisher = new ros::Publisher(m_handle_name.c_str(), &m_ultrasonic_msg);

    m_publish_data_sub = new ros::Subscriber<std_msgs::Empty, ADIUltrasonicNode>
        (m_sub_publish_data_name.c_str(), &ADIUltrasonicNode::m_publishData, this);
}

ADIUltrasonicNode::ADIUltrasonicNode(NodeManager* node_manager, pros::ext_adi_port_tuple_t port_tuple,
     std::string handle_name) : Node(node_manager, 10),
    m_ultrasonic(port_tuple) {
    m_handle_name = handle_name.insert(0, "sensor/");
    m_sub_publish_data_name = m_handle_name + "/publish";

    m_publisher = new ros::Publisher(m_handle_name.c_str(), &m_ultrasonic_msg);

    m_publish_data_sub = new ros::Subscriber<std_msgs::Empty, ADIUltrasonicNode>
        (m_sub_publish_data_name.c_str(), &ADIUltrasonicNode::m_publishData, this);
}

void ADIUltrasonicNode::m_publishData(const std_msgs::Empty& msg) {
    m_populateMessage();
    m_publisher->publish(&m_ultrasonic_msg);
}

void ADIUltrasonicNode::initialize() {
    // Initialize the handler, and set up data to publish
    m_handle->initNode();
    m_handle->advertise(*m_publisher);
}

int ADIUltrasonicNode::getValue() {
    return m_ultrasonic.get_value();
}

void ADIUltrasonicNode::teleopPeriodic() {
    
}

void ADIUltrasonicNode::autonPeriodic() {
    
}

void ADIUltrasonicNode::m_populateMessage() {
    m_ultrasonic_msg.data = getValue();
}

ADIUltrasonicNode::~ADIUltrasonicNode() { 
    delete m_publisher;
}