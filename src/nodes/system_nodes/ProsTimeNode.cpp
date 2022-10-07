#include "lib-rr/nodes/system_nodes/ProsTimeNode.h"

ProsTimeNode::ProsTimeNode(NodeManager* node_manager, std::string handle_name) 
    : Node (node_manager, 50) {
    m_handle_name = handle_name.insert(0, "prosTime/");
    m_sub_publish_data_name = m_handle_name + "/publish";

    m_publisher = new ros::Publisher(m_handle_name.c_str(), &m_pros_time_msg);

    m_publish_data_sub = new ros::Subscriber<std_msgs::Empty, ProsTimeNode>
        (m_sub_publish_data_name.c_str(), &ProsTimeNode::m_publishData, this);
}

void ProsTimeNode::m_publishData(const std_msgs::Empty& msg) {
    m_populateMessage();
    m_publisher->publish(&m_pros_time_msg);
}

void ProsTimeNode::initialize() {
    // Initialize the handler, and set up data to publish
    Node::m_handle->advertise(*m_publisher);
}

int ProsTimeNode::getValue() {
    return pros::millis();
}

void ProsTimeNode::teleopPeriodic() {

}

void ProsTimeNode::autonPeriodic() {

}

void ProsTimeNode::m_populateMessage() {
    m_pros_time_msg.data = pros::millis();
}

ProsTimeNode::~ProsTimeNode() {
    delete m_publisher;
}