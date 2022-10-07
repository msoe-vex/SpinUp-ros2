#include "lib-rr/nodes/sensor_nodes/ADIPotentiometerNode.h"

// By default, this constructor calls the constructor for the Node object in
// NodeManager.h
ADIPotentiometerNode::ADIPotentiometerNode(NodeManager* node_manager, int port,
    std::string handle_name, pros::adi_potentiometer_type_e potType) : Node(node_manager, 10), 
    m_potentiometer(port, potType) {
    m_handleName = handle_name.insert(0, "sensor/");
    m_subPublishDataName = m_handleName + "/publish";

    m_publisher = new ros::Publisher(m_handleName.c_str(), &m_potentiometerMsg);

    m_publishDataSub = new ros::Subscriber<std_msgs::Empty, ADIPotentiometerNode>
        (m_subPublishDataName.c_str(), &ADIPotentiometerNode::m_publishData, this);
}

ADIPotentiometerNode::ADIPotentiometerNode(NodeManager* node_manager, pros::ext_adi_port_pair_t port_pair,
    std::string handle_name, pros::adi_potentiometer_type_e potType) : Node(node_manager, 10), 
    m_potentiometer(port_pair, potType) {
    m_handleName = handle_name.insert(0, "sensor/");
    m_subPublishDataName = m_handleName + "/publish";

    m_publisher = new ros::Publisher(m_handleName.c_str(), &m_potentiometerMsg);

    m_publishDataSub = new ros::Subscriber<std_msgs::Empty, ADIPotentiometerNode>
        (m_subPublishDataName.c_str(), &ADIPotentiometerNode::m_publishData, this);
}

void ADIPotentiometerNode::m_publishData(const std_msgs::Empty& msg) {
    m_populateMessage();
    m_publisher->publish(&m_potentiometerMsg);
}

void ADIPotentiometerNode::initialize() {
    // Initialize the handler, and set up data to publish
    Node::m_handle->advertise(*m_publisher);
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

void ADIPotentiometerNode::m_populateMessage() {
    m_potentiometerMsg.data = m_potentiometer.get_angle();
}

ADIPotentiometerNode::~ADIPotentiometerNode() { 
    delete m_publisher; 
}