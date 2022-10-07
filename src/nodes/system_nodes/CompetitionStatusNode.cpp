#include "lib-rr/nodes/system_nodes/CompetitionStatusNode.h"

CompetitionStatusNode::CompetitionStatusNode (NodeManager* node_manager, 
    std::string handle_name) : Node(node_manager, 100) {
    m_handle_name = handle_name.insert(0, "compStatus/");
    m_sub_publish_data_name = m_handle_name + "/publish";

    m_publisher = new ros::Publisher(m_handle_name.c_str(), &m_comp_status_msg);

    m_publish_data_sub = new ros::Subscriber<std_msgs::Empty, CompetitionStatusNode>
        (m_sub_publish_data_name.c_str(), &CompetitionStatusNode::m_publishData, this);
}

void CompetitionStatusNode::m_publishData(const std_msgs::Empty& msg) {
    m_populateMessage();
    m_publisher->publish(&m_comp_status_msg);
}

void CompetitionStatusNode::initialize() {
    Node::m_handle->advertise(*m_publisher);
}

void CompetitionStatusNode::teleopPeriodic() {
    
}

void CompetitionStatusNode::autonPeriodic() {
    
}

void CompetitionStatusNode::m_populateMessage() {
    m_comp_status_msg.status = pros::competition::get_status();
    m_comp_status_msg.is_autonomous = pros::competition::is_autonomous();
    m_comp_status_msg.is_comp_connected = pros::competition::is_connected();
    m_comp_status_msg.is_disabled = pros::competition::is_disabled();
}

CompetitionStatusNode::~CompetitionStatusNode () {
    delete m_publisher;
}
