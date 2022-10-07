#include "lib-rr/nodes/system_nodes/BatteryNode.h"

BatteryNode::BatteryNode (NodeManager* node_manager, std::string handle_name)
     : Node (node_manager, 200) {
    m_handle_name = handle_name.insert(0, "battery/");
    m_sub_publish_data_name = m_handle_name + "/publish";

    m_publisher = new ros::Publisher(m_handle_name.c_str(), &m_battery_msg);
    
    m_publish_data_sub = new ros::Subscriber<std_msgs::Empty, BatteryNode>
        (m_sub_publish_data_name.c_str(), &BatteryNode::m_publishData, this);
}

void BatteryNode::m_publishData(const std_msgs::Empty& msg) {
    m_populateMessage();
    m_publisher->publish(&m_battery_msg);
}

void BatteryNode::initialize() {
    // Initialize the handler, and set up data to publish
    Node::m_handle->advertise(*m_publisher);
}

void BatteryNode::teleopPeriodic() {
    
}

void BatteryNode::autonPeriodic() {
    
}

void BatteryNode::m_populateMessage () {
    m_battery_msg.capacity = pros::battery::get_capacity();
    m_battery_msg.current = pros::battery::get_current();
    m_battery_msg.temperature = pros::battery::get_temperature();
    m_battery_msg.voltage = pros::battery::get_temperature();
}

BatteryNode::~BatteryNode() {
    delete m_publisher;
}