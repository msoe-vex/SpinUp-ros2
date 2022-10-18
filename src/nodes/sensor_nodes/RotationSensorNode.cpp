#include "nodes/sensor_nodes/RotationSensorNode.h"

RotationSensorNode::RotationSensorNode(NodeManager* node_manager, 
    int rotation_port, std::string handle_name) : Node (node_manager, 20), 
    m_rotation_sensor(rotation_port) {
    m_handle_name = handle_name.insert(0, "sensor/");
}

void RotationSensorNode::initialize() {
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

RotationSensorNode::~RotationSensorNode () {
}