#include "nodes/SwerveDriveNode.h"

// By default, this constructor calls the constructor for the Node object in
// NodeManager.h
DriverControlNode::DriverControlNode(NodeManager* node_manager, MotorNode* left_swerve_1, MotorNode* left_swerve_2, 
        ADIAnalogInNode* left_swerve_pot, MotorNode* right_swerve_1, MotorNode* right_swerve_2, 
        ADIAnalogInNode* right_swerve_pot, MotorNode* rear_swerve_1, MotorNode* rear_swerve_2, 
        ADIAnalogInNode* rear_swerve_pot, InertialSensorNode* inertial_sensor, ControllerNode* controller_primary) : Node(node_manager, 20), 
    swerveController(left_module_location, right_module_location, rear_module_location, kP, kI, kD), 
    left_swerve_1(left_swerve_1), left_swerve_2(left_swerve_2), left_swerve_pot(left_swerve_pot), 
    right_swerve_1(right_swerve_1), right_swerve_2(right_swerve_2), right_swerve_pot(right_swerve_pot), 
    rear_swerve_1(rear_swerve_1), rear_swerve_2(rear_swerve_2), rear_swerve_pot(rear_swerve_pot), 
    inertial_sensor(inertial_sensor), controller_primary(controller_primary->getController()) {

    left_module_location(0) = LEFT_MODULE_LOCATION_X;
    left_module_location(1) = LEFT_MODULE_LOCATION_Y;
    right_module_location(0) = RIGHT_MODULE_LOCATION_X;
    right_module_location(1) = RIGHT_MODULE_LOCATION_Y;
    rear_module_location(0) = REAR_MODULE_LOCATION_X;
    rear_module_location(1) = REAR_MODULE_LOCATION_Y;
}

void DriverControlNode::initialize() {
    
}

void DriverControlNode::teleopPeriodic() {
    robot_angle = inertial_sensor->getYaw();
    
    controller_target_velocity(0) = (controller_primary->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) / 127.0) * MAX_VELOCITY;
    controller_target_velocity(1) = (controller_primary->get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0) * MAX_VELOCITY;
    rotation_velocity = -(controller_primary->get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127.0) * MAX_ROTATIONAL_VELOCITY;

    field_target_velocity = robot_angle.inverse() * controller_target_velocity;

    swerveController.assignActualAngle(left_swerve_pot->getValue(), right_swerve_pot->getValue(), rear_swerve_pot->getValue());

    MotorPowers left_motor_powers = swerveController.calculateLeftModule(field_target_velocity, rotation_velocity);
    MotorPowers right_motor_powers = swerveController.calculateRightModule(field_target_velocity, rotation_velocity);
    MotorPowers rear_motor_powers = swerveController.calculateRearModule(field_target_velocity, rotation_velocity);

    left_swerve_1->move(left_motor_powers.left_motor_power);
    left_swerve_2->move(left_motor_powers.right_motor_power);

    right_swerve_1->move(right_motor_powers.left_motor_power);
    right_swerve_2->move(right_motor_powers.right_motor_power);

    rear_swerve_1->move(rear_motor_powers.left_motor_power);
    rear_swerve_2->move(rear_motor_powers.right_motor_power);
}

void DriverControlNode::autonPeriodic() {
    
}

DriverControlNode::~DriverControlNode() { 
    delete m_publisher; 
}
