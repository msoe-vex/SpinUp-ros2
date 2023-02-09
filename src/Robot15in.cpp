#include "Robot15in.h"

// Initializes 15in robot
void Robot15in::initialize() { 
    pros::lcd::initialize();
    node_manager = new NodeManager(pros::millis);
    primary_controller = new ControllerNode(node_manager, "primary");

    /* Define the drivetrain components */
    // For the 15in X-Drive `_2` motors are the ones on the top of the other motors
    left_front_drive = new MotorNode(node_manager, 15, "leftFrontDrive", true); // previously 16
    left_front_drive_2 = new MotorNode(node_manager, 18, "leftFrontTopDrive", false);
    left_rear_drive = new MotorNode(node_manager, 8, "leftRearDrive", true);
    left_rear_drive_2 = new MotorNode(node_manager, 9, "leftRearTopDrive", false);

    right_front_drive = new MotorNode(node_manager, 13, "rightFrontDrive", false);
    right_front_drive_2 = new MotorNode(node_manager, 1, "rightFrontTopDrive", true);
    right_rear_drive = new MotorNode(node_manager, 4, "rightRearDrive", false); // 2 is ded
    right_rear_drive_2 = new MotorNode(node_manager, 3, "rightRearTopDrive", true); // prev 3

    HolonomicDriveNode::HolonomicEightMotors holonomic_drive_motors = {
        left_front_drive,  left_front_drive_2, left_rear_drive,
        left_rear_drive_2, right_front_drive,  right_front_drive_2,
        right_rear_drive,  right_rear_drive_2};

    EncoderConfig holonomic_encoder_config = {
        0,   // Initial ticks
        360, // Ticks per Rotation
        3.75 // Wheel diameter
    };

    HolonomicDriveKinematics::HolonomicWheelLocations holonomic_wheel_locations =
        {
            Vector2d(-5.48, 5.48),  // Left front
            Vector2d(-5.48, -5.48), // Left rear
            Vector2d(5.48, 5.48),   // Right front
            Vector2d(5.48, -5.48)   // Right rear
        };

    encoder = new ADIEncoderNode(node_manager, 'C', 'D', "encoder");        

    inertial_sensor =
        new InertialSensorNode(node_manager, "inertialSensor", 10); 

    HolonomicDriveKinematics holonomic_drive_kinematics(
        holonomic_encoder_config, holonomic_wheel_locations);

    holonomic_drive_node = new HolonomicDriveNode(
        node_manager, "drivetrain", primary_controller, inertial_sensor,
        holonomic_drive_motors, holonomic_drive_kinematics);

    /* Define the intake components */
    intake_motor = new MotorNode(node_manager, 5, "intake", true);
    indexer_motor = new MotorNode(node_manager, 6, "indexer", false);
    shooter_motor = new MotorNode(node_manager, 14, "shooter", true);
    shooter_motor_2 = new MotorNode(node_manager, 17, "shooter2", true);

    intake_node = new IntakeNode(node_manager, "intake", 
    primary_controller, pros::E_CONTROLLER_DIGITAL_R1, pros::E_CONTROLLER_DIGITAL_R2, intake_motor);	

    indexer_node = new IntakeNode(node_manager, "indexer", 
    primary_controller, pros::E_CONTROLLER_DIGITAL_R1, pros::E_CONTROLLER_DIGITAL_R2, indexer_motor);	


    shooter_node = new ShooterNode(node_manager, "shooter", 
    primary_controller, pros::E_CONTROLLER_DIGITAL_L1, shooter_motor, shooter_motor_2);	
}

void Robot15in::disabled() {}

void Robot15in::competition_initialize() {}

void Robot15in::autonomous() {}

// Must put all telepPeriodic() method from each class into here
void Robot15in::opcontrol() {
    while (true) {
        // nodeManager->executeTeleop();
        holonomic_drive_node->teleopPeriodic();
        intake_node->teleopPeriodic();
        indexer_node->teleopPeriodic();
        shooter_node->teleopPeriodic();
        encoder->teleopPeriodic();
        inertial_sensor->teleopPeriodic();
    }
}
