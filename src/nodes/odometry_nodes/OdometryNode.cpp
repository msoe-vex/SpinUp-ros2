#include "lib-rr/nodes/odometry_nodes/OdometryNode.h"

OdometryNode::OdometryNode(NodeManager* node_manager, std::string handle_name, 
        ADIEncoderNode* odom_encoder_1, ADIEncoderNode* odom_encoder_2, InertialSensorNode* inertial_sensor_node, 
        OdomConfig odom_config, IOdometry::EncoderLocations locations) : Node(node_manager, 50), m_handle_name(handle_name),
        m_odom_encoder_1(odom_encoder_1), m_odom_encoder_2(odom_encoder_2), m_inertial_sensor_node(inertial_sensor_node),
        m_current_angle_offset(0), m_odom_config(odom_config), m_locations(locations) {
    m_odom = m_getOdomClass(odom_config);
}

OdometryNode::OdometryNode(NodeManager* node_manager, std::string handle_name, 
        MotorNode* motor_1, MotorNode* motor_2, InertialSensorNode* inertial_sensor_node, 
        OdomConfig odom_config, IOdometry::EncoderLocations locations) : Node(node_manager, 50), m_handle_name(handle_name),
        m_motor_1(motor_1), m_motor_2(motor_2), m_inertial_sensor_node(inertial_sensor_node),
        m_current_angle_offset(0), m_odom_config(odom_config), m_locations(locations) {
    m_odom = m_getOdomClass(odom_config);
}

IOdometry* OdometryNode::m_getOdomClass(OdomConfig config) {
    EncoderConfig adi_encoder_config = {0., 2400., 1.975};
    EncoderConfig v5_integrated_encoder_config = {0., 900., 4.0625};

    switch (config) {
        case FOLLOWER:
            return new FollowerOdometry(adi_encoder_config, adi_encoder_config, m_locations);
        case TANK:
            return new TankOdometry(v5_integrated_encoder_config, v5_integrated_encoder_config, m_locations);
        default:
            Node::m_handle->logerror("Error creating odometry instance in OdometryNode.cpp");
            return new FollowerOdometry(adi_encoder_config, adi_encoder_config, m_locations);
    }
}

void OdometryNode::initialize() {
    // Calibrate the gyro, and reset the orientation with the correct gyro angle
    m_inertial_sensor_node->reset();
	setCurrentPose(Pose(Vector2d(0, 0), m_inertial_sensor_node->getYaw()));

    m_timer.Start();
}

void OdometryNode::setCurrentPose(Pose pose) {
    m_odom->SetCurrentPose(pose);
}

Pose OdometryNode::getCurrentPose() {
    return m_odom->GetPose();
}

void OdometryNode::teleopPeriodic() {
    m_odom->Update(m_odom_encoder_1->getValue(), m_odom_encoder_2->getValue(), m_inertial_sensor_node->getYaw());
    
    Pose currentPose = m_odom->GetPose();
    float x = currentPose.position.x();
    float y = currentPose.position.y();
    float angle = currentPose.angle.angle();

    pros::lcd::print(0, "Position: (%.2f, %.2f)\n", x, y);
    pros::lcd::print(1, "Angle: %.2f", angle);

    // if (m_timer.Get() - lastTime > delayTime) {
    //     std::cout << "X Pos: " << m_odom->GetPose().position.x() << " | Y Pos: " << m_odom->GetPose().position.y() << " | Angle: " << m_odom->GetPose().angle.angle() << std::endl;
    //     lastTime = m_timer.Get();
    // }
}

void OdometryNode::autonPeriodic() {
    m_odom->Update(m_odom_encoder_1->getValue(), m_odom_encoder_2->getValue(), m_inertial_sensor_node->getYaw());

    Pose currentPose = m_odom->GetPose();
    float x = currentPose.position.x();
    float y = currentPose.position.y();
    float angle = currentPose.angle.angle();
    
    pros::lcd::print(0, "Position: (%.2f, %.2f)\n", x, y);
    pros::lcd::print(1, "Angle: %.2f", angle);
}

OdometryNode::~OdometryNode() {
    delete m_odom;
}