#include "Robot18in.h"

// Initializes 18in robot
void Robot18in::initialize() {
    pros::lcd::initialize();
    node_manager = new NodeManager(pros::millis);
    primary_controller = new ControllerNode(node_manager, "primary");

    /* Define the drivetrain components */
    left_front_drive = new MotorNode(node_manager, 15, "leftFrontDrive", true); // previously 16
    left_front_drive_2 = new MotorNode(node_manager, 18, "leftFrontTopDrive", false);
    left_rear_drive = new MotorNode(node_manager, 8, "leftRearDrive", true);
    left_rear_drive_2 = new MotorNode(node_manager, 9, "leftRearTopDrive", false);

    right_front_drive = new MotorNode(node_manager, 13, "rightFrontDrive", false);
    right_front_drive_2 = new MotorNode(node_manager, 1, "rightFrontTopDrive", true);
    right_rear_drive = new MotorNode(node_manager, 4, "rightRearDrive", false); // 2 is ded
    right_rear_drive_2 = new MotorNode(node_manager, 3, "rightRearTopDrive", true); // prev 3

    TankDriveNode::TankEightMotors tank_drive_motors = {
        left_front_drive,  left_front_drive_2, left_rear_drive,
        left_rear_drive_2, right_front_drive,  right_front_drive_2,
        right_rear_drive,  right_rear_drive_2
    };

    TankDriveKinematics::TankWheelLocations tank_wheel_locations = {
        Vector2d(0, 0),  // Left
        Vector2d(0, 0)    // Right
    };

    EncoderConfig encoder_config = {
		0, // Initial ticks
		900., // Ticks per RPM
		3.25 // Wheel diameter
	};

    tank_kinematics = new TankDriveKinematics(encoder_config, tank_wheel_locations);

    tank_drive_node = new TankDriveNode(
            node_manager, "tankDrive", primary_controller,
            tank_drive_motors, *tank_kinematics
    );

    encoder = new ADIEncoderNode(node_manager, 'C', 'D', "encoder");        

    // TODO: PUT A GYRO ON THE ROBOT
    // Also put the right port here
    inertial_sensor = new InertialSensorNode(node_manager, "inertialSensor", 10); 

    /* Define the intake components */
    intake_motor = new MotorNode(node_manager, 5, "intake", true);
    indexer_motor = new MotorNode(node_manager, 7, "indexer", true);
    shooter_motor = new MotorNode(node_manager, 11, "shooter", true);
    shooter_motor_2 = new MotorNode(node_manager, 12, "shooter2", true);

    intake_node = new IntakeNode(
            node_manager, "intake", primary_controller, 
            pros::E_CONTROLLER_DIGITAL_R1, pros::E_CONTROLLER_DIGITAL_R2, {intake_motor}
    );	

    indexer_node = new IntakeNode(
            node_manager, "indexer", primary_controller, 
            pros::E_CONTROLLER_DIGITAL_X, pros::E_CONTROLLER_DIGITAL_Y, {indexer_motor}
    );	

    shooter_node = new ShooterNode(
            node_manager, "shooter", primary_controller, 
            pros::E_CONTROLLER_DIGITAL_L1, {shooter_motor, shooter_motor_2}
    );	
}

void Robot18in::disabled() {}

void Robot18in::competition_initialize() {}

void Robot18in::autonomous() {}

// Must put all telepPeriodic() method from each class into here
void Robot18in::opcontrol() {
    while (true) {
        // nodeManager->executeTeleop();
        tank_drive_node->teleopPeriodic();
        intake_node->teleopPeriodic();
        indexer_node->teleopPeriodic();
        shooter_node->teleopPeriodic();
        encoder->teleopPeriodic();
        inertial_sensor->teleopPeriodic();
    }
}
