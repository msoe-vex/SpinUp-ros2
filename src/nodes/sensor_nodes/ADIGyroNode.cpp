#include "lib-rr/nodes/sensor_nodes/ADIGyroNode.h"

// By default, this constructor calls the constructor for the Node object in
// NodeManager.h
ADIGyroNode::ADIGyroNode(NodeManager* node_manager, int port, double multiplier,
    std::string handle_name) : Node(node_manager, 10), m_gyro(port, multiplier) {
    m_handle_name = handle_name.insert(0, "sensor/");
    m_sub_publish_data_name = m_handle_name + "/publish";

    m_publisher = new ros::Publisher(m_handle_name.c_str(), &m_gyro_msg);

    m_publish_data_sub = new ros::Subscriber<std_msgs::Empty, ADIGyroNode>
        (m_sub_publish_data_name.c_str(), &ADIGyroNode::m_publishData, this);
}

ADIGyroNode::ADIGyroNode(NodeManager* node_manager, pros::ext_adi_port_pair_t port_pair, 
    double multiplier, std::string handle_name) : 
    Node(node_manager, 10), m_gyro(port_pair, multiplier) {
    m_handle_name = handle_name.insert(0, "sensor/");
    m_sub_publish_data_name = m_handle_name + "/publish";

    m_publisher = new ros::Publisher(m_handle_name.c_str(), &m_gyro_msg);

    m_publish_data_sub = new ros::Subscriber<std_msgs::Empty, ADIGyroNode>
        (m_sub_publish_data_name.c_str(), &ADIGyroNode::m_publishData, this);
}

void ADIGyroNode::m_publishData(const std_msgs::Empty& msg) {
    m_populateMessage();
    m_publisher->publish(&m_gyro_msg);
}

void ADIGyroNode::initialize() {
    // Initialize the handler, and set up data to publish
    Node::m_handle->advertise(*m_publisher);
}

float ADIGyroNode::getValue() {
    return m_gyro.get_value();
}

void ADIGyroNode::teleopPeriodic() {
    
}

void ADIGyroNode::autonPeriodic() {
    
}

void ADIGyroNode::m_populateMessage() { 
    m_gyro_msg.data = m_gyro.get_value();
}

ADIGyroNode::~ADIGyroNode() { 
    delete m_publisher;
}