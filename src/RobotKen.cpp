#include "RobotKen.h"

// Initializes 18in robot
void RobotKen::initialize() {
    pros::lcd::initialize();
    node_manager = new NodeManager(pros::millis);
    primary_controller = new ControllerNode(node_manager, "primary");

    /* Define the drivetrain components */
    left_drive_1 = new MotorNode(node_manager, 8, "leftDrive1", false); 
    left_drive_2 = new MotorNode(node_manager, 9, "leftDrive2", true);
    left_drive_3 = new MotorNode(node_manager, 14, "leftDrive3", true); // Not in use for symmetry
    left_drive_4 = new MotorNode(node_manager, 10, "LeftDrive4", false);
    // 1, 4, 17`, 6
    right_drive_1 = new MotorNode(node_manager, 1, "rightDrive1", true);
    right_drive_2 = new MotorNode(node_manager, 4, "rightDrive2", false);
    right_drive_3 = new MotorNode(node_manager, 17, "rightRearDrive", false); // Not in use due to ded motor
    right_drive_4 = new MotorNode(node_manager, 6, "rightRearTopDrive", true); 

    TankDriveNode::TankEightMotors tank_drive_motors = {
        left_drive_1,  left_drive_2, left_drive_3,
        left_drive_4, right_drive_1,  right_drive_2,
        right_drive_3,  right_drive_4
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

    /* Define the intake components */
    intake_motor = new MotorNode(node_manager, 16, "intake", false);
    indexer_motor = new MotorNode(node_manager, 13, "indexer", false);

    intake_node = new IntakeNode(
            node_manager, "intake", primary_controller, 
            pros::E_CONTROLLER_DIGITAL_A, pros::E_CONTROLLER_DIGITAL_B, {intake_motor}
    );	

    indexer_node = new IntakeNode(
            node_manager, "indexer", primary_controller, 
            pros::E_CONTROLLER_DIGITAL_A, pros::E_CONTROLLER_DIGITAL_B, {indexer_motor}
    );

    /* Define the Roller Components */
    roller_motor = new MotorNode(node_manager, 11, "roller", true);	

    roller_node = new IntakeNode(
            node_manager, "roller", primary_controller, 
            pros::E_CONTROLLER_DIGITAL_L1, pros::E_CONTROLLER_DIGITAL_L2, {roller_motor}
    );
}

void RobotKen::disabled() {}

void RobotKen::competition_initialize() {}

void RobotKen::autonomous() {}

// Must put all telepPeriodic() method from each class into here
void RobotKen::opcontrol() {
    while (true) {
        // nodeManager->executeTeleop();
        tank_drive_node->teleopPeriodic();
        intake_node->teleopPeriodic();
        indexer_node->teleopPeriodic();
        roller_node->teleopPeriodic();
    }
}
