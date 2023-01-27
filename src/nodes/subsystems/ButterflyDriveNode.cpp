#include "ButterflyDriveNode.h"
#include "kinematics/IDriveKinematics.h"

ButterflyDriveNode::ButterflyDriveNode(NodeManager *node_manager, std::string handle_name, ControllerNode *controller,
    InertialSensorNode *inertial_sensor, ButterflyEightMotors motors, HolonomicDriveKinematics holo_kinematics, TankDriveKinematics tank_kinematics) : 
        IDriveNode(node_manager), 
        m_controller(controller->getController()),
        m_inertial_sensor(inertial_sensor),
        m_motors(motors),
        m_holo_kinematics(holo_kinematics),
        m_tank_kinematics(tank_kinematics) {
    m_handle_name = handle_name.insert(0, "robot/");
    m_drive_mode = DriveMode::Holonomic;
}

IDriveKinematics & ButterflyDriveNode::m_getCurrentDriveKinematics() {
    switch (this->m_drive_mode) {
        case Tank:
            return this->m_tank_kinematics;
            break;

        case Holonomic:
            return this->m_holo_kinematics;
            break;
    }
}

void ButterflyDriveNode::m_setLeftFrontVoltage(int voltage) {
    m_motors.left_front_motor->moveVoltage(voltage);
    m_motors.left_front_motor_2->moveVoltage(voltage);
}

void ButterflyDriveNode::m_setLeftRearVoltage(int voltage) {
    m_motors.left_rear_motor->moveVoltage(voltage);
    m_motors.left_rear_motor_2->moveVoltage(voltage);
}

void ButterflyDriveNode::m_setRightFrontVoltage(int voltage) {
    m_motors.right_front_motor->moveVoltage(voltage);
    m_motors.right_front_motor_2->moveVoltage(voltage);
}

void ButterflyDriveNode::m_setRightRearVoltage(int voltage) {
    m_motors.right_rear_motor->moveVoltage(voltage);
    m_motors.right_rear_motor_2->moveVoltage(voltage);
}

void ButterflyDriveNode::m_setLeftFrontVelocity(float velocity) {
    m_motors.left_front_motor->moveVelocity(velocity);
    m_motors.left_front_motor_2->moveVelocity(velocity);
}

void ButterflyDriveNode::m_setLeftRearVelocity(float velocity) {
    m_motors.left_rear_motor->moveVelocity(velocity);
    m_motors.left_rear_motor_2->moveVelocity(velocity);
}

void ButterflyDriveNode::m_setRightFrontVelocity(float velocity) {
    m_motors.right_front_motor->moveVelocity(velocity);
    m_motors.right_front_motor_2->moveVelocity(velocity);
}

void ButterflyDriveNode::m_setRightRearVelocity(float velocity) {
    m_motors.right_rear_motor->moveVelocity(velocity);
    m_motors.right_rear_motor_2->moveVelocity(velocity);
}

void ButterflyDriveNode::initialize() {
    resetEncoders();
}

void ButterflyDriveNode::resetEncoders() {
    m_motors.left_front_motor->resetEncoder();
    m_motors.left_front_motor_2->resetEncoder();
    m_motors.left_rear_motor->resetEncoder();
    m_motors.left_rear_motor_2->resetEncoder();
    m_motors.right_front_motor->resetEncoder();
    m_motors.right_front_motor_2->resetEncoder();
    m_motors.right_rear_motor->resetEncoder();
    m_motors.right_rear_motor_2->resetEncoder();
}

IDriveNode::FourMotorDriveEncoderVals ButterflyDriveNode::getIntegratedEncoderVals() {
    return FourMotorDriveEncoderVals {
        m_motors.left_front_motor->getPosition(),
        m_motors.left_rear_motor->getPosition(),
        m_motors.right_front_motor->getPosition(),
        m_motors.right_rear_motor->getPosition()
    };
}

void ButterflyDriveNode::m_fieldOrientedControl() {
    controller_target_velocity(0) = (m_controller->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) / 127.0) * MAX_VELOCITY;
    controller_target_velocity(1) = (m_controller->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0) * MAX_VELOCITY;
    rotation_velocity = -(m_controller->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127.0) * MAX_VELOCITY;

    field_target_velocity = m_inertial_sensor->getYaw().inverse() * Rotation2Dd(GYRO_OFFSET) * controller_target_velocity;
    setDriveVelocity(field_target_velocity.x(), field_target_velocity.y(), rotation_velocity);
}

void ButterflyDriveNode::m_tankControl() {
    int left_x = (m_controller->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) / 127.0) * MAX_MOTOR_VOLTAGE;
    int left_y = (m_controller->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0) * MAX_MOTOR_VOLTAGE;
    
    int right_x = (m_controller->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127.0) * MAX_MOTOR_VOLTAGE;
    int right_y = (m_controller->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) / 127.0) * MAX_MOTOR_VOLTAGE;

    setDriveVoltage(left_x, left_y, right_x, right_y);
}

void ButterflyDriveNode::setDriveVoltage(int x_voltage, int theta_voltage) {
    setDriveVoltage(x_voltage, 0, theta_voltage);
}

void ButterflyDriveNode::setDriveVoltage(int x_voltage, int y_voltage, int theta_voltage) {
    IDriveKinematics::FourMotorPercentages motor_percentages = 
        this->m_getCurrentDriveKinematics().inverseKinematics(x_voltage, y_voltage, theta_voltage, MAX_MOTOR_VOLTAGE);

    m_setLeftFrontVoltage(motor_percentages.left_front_percent * MAX_MOTOR_VOLTAGE);
    m_setLeftRearVoltage(motor_percentages.left_rear_percent * MAX_MOTOR_VOLTAGE);
    m_setRightFrontVoltage(motor_percentages.right_front_percent * MAX_MOTOR_VOLTAGE);
    m_setRightRearVoltage(motor_percentages.right_rear_percent * MAX_MOTOR_VOLTAGE);
}

void ButterflyDriveNode::setDriveVoltage(int left_x, int left_y, int right_x, int right_y) {
    IDriveKinematics::FourMotorPercentages motor_percentages = 
        this->m_getCurrentDriveKinematics().simpleKinematics(0, left_y, 0, right_y, MAX_MOTOR_VOLTAGE);

    m_setLeftFrontVoltage(motor_percentages.left_front_percent * MAX_MOTOR_VOLTAGE);
    m_setLeftRearVoltage(motor_percentages.left_rear_percent * MAX_MOTOR_VOLTAGE);
    m_setRightFrontVoltage(motor_percentages.right_front_percent * MAX_MOTOR_VOLTAGE);
    m_setRightRearVoltage(motor_percentages.right_rear_percent * MAX_MOTOR_VOLTAGE);
}

void ButterflyDriveNode::setDriveVelocity(float x_velocity, float theta_velocity) {
    setDriveVelocity(x_velocity, 0, theta_velocity);
}

void ButterflyDriveNode::setDriveVelocity(float x_velocity, float y_velocity, float theta_velocity) {
    IDriveKinematics::FourMotorPercentages motor_percentages = 
        this->m_getCurrentDriveKinematics().inverseKinematics(x_velocity, y_velocity, theta_velocity, MAX_VELOCITY);

    m_setLeftFrontVelocity(motor_percentages.left_front_percent * MAX_VELOCITY);
    m_setLeftRearVelocity(motor_percentages.left_rear_percent * MAX_VELOCITY);
    m_setRightFrontVelocity(motor_percentages.right_front_percent * MAX_VELOCITY);
    m_setRightRearVelocity(motor_percentages.right_rear_percent * MAX_VELOCITY);
}