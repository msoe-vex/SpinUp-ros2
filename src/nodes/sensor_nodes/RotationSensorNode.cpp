#include "lib-rr/nodes/sensor_nodes/RotationSensorNode.h"

RotationSensorNode::RotationSensorNode(NodeManager* node_manager, 
    int rotation_port, std::string handle_name) : Node (node_manager, 20), 
    m_rotation_sensor(rotation_port) {
    m_handle_name = handle_name.insert(0, "sensor/");
    m_sub_publish_data_name = m_handle_name + "/publish";

    m_publisher = new ros::Publisher(m_handle_name.c_str(), &m_rotation_msg);

    m_publish_data_sub = new ros::Subscriber<std_msgs::Empty, RotationSensorNode>
        (m_sub_publish_data_name.c_str(), &RotationSensorNode::m_publishData, this);
}

void RotationSensorNode::m_publishData(const std_msgs::Empty& msg) {
    m_populateMessage();
    m_publisher->publish(&m_rotation_msg);
}

void RotationSensorNode::initialize() {
    // Initialize the handler, and set up data to publish
    Node::m_handle->advertise(*m_publisher);
}

int RotationSensorNode::getAngle() {
    return m_rotation_sensor.get_angle();
}

int RotationSensorNode::getPosition() {
    return m_rotation_sensor.get_position();
}

int RotationSensorNode::getVelocity() {
    return m_rotation_sensor.get_velocity();
}

void RotationSensorNode::teleopPeriodic() {

}

void RotationSensorNode::autonPeriodic() {

}

void RotationSensorNode::m_populateMessage() {
    m_rotation_msg.encoder_angle = getAngle();
    m_rotation_msg.encoder_position = getPosition();
    m_rotation_msg.encoder_velocity = getVelocity();
}

RotationSensorNode::~RotationSensorNode () {
    delete m_publisher;
}