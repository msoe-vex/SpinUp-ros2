#include "Robot15in.h"

// Initializes 15in robot
void Robot15in::initialize() { 
    pros::lcd::initialize();
    node_manager = new NodeManager(pros::millis);
    primary_controller = new ControllerNode(node_manager, "primary");

    /* Define the drivetrain components */
    // For the 15in X-Drive `_2` motors are the ones on the top of the other motors
    left_front_drive = new MotorNode(node_manager, 17, "leftFrontDrive", true); // previously 16
    left_front_drive_2 = new MotorNode(node_manager, 18, "leftFrontTopDrive", false);
    left_rear_drive = new MotorNode(node_manager, 15, "leftRearDrive", true);
    left_rear_drive_2 = new MotorNode(node_manager, 11, "leftRearTopDrive", false);

    right_front_drive = new MotorNode(node_manager, 13, "rightFrontDrive", false);
    right_front_drive_2 = new MotorNode(node_manager, 14, "rightFrontTopDrive", true);
    right_rear_drive = new MotorNode(node_manager, 9, "rightRearDrive", false); // 2 is ded
    right_rear_drive_2 = new MotorNode(node_manager, 10, "rightRearTopDrive", true); // prev 3

    HolonomicDriveNode::HolonomicEightMotors holonomic_drive_motors = {
        left_front_drive,  left_front_drive_2, left_rear_drive,
        left_rear_drive_2, right_front_drive,  right_front_drive_2,
        right_rear_drive,  right_rear_drive_2
    };

    EncoderConfig holonomic_encoder_config = {
        0,   // Initial ticks
        360, // Ticks per Rotation
        3.75 // Wheel diameter
    };

    HolonomicDriveKinematics::HolonomicWheelLocations holonomic_wheel_locations = {
        Vector2d(-5.48, 5.48),  // Left front
        Vector2d(-5.48, -5.48), // Left rear
        Vector2d(5.48, 5.48),   // Right front
        Vector2d(5.48, -5.48)   // Right rear
    };

    encoder = new ADIEncoderNode(node_manager, 'C', 'D', "encoder");        

    /* Define the Odometry components*/
    x_odom_encoder = new ADIEncoderNode(node_manager, 'A', 'B', "xOdomEncoder", false);
    y_odom_encoder = new ADIEncoderNode(node_manager, 'C', 'D', "yOdomEncoder", false);

    IOdometry::EncoderLocations encoderLocations {
		Vector2d(0.606, -5.638),
		Vector2d(-2.624, 4.446)
	};

    inertial_sensor = new InertialSensorNode(node_manager, "inertialSensor", 20); 

    odom_node = new OdometryNode(node_manager, "odometry", x_odom_encoder,
            y_odom_encoder, inertial_sensor, OdometryNode::FOLLOWER, encoderLocations);

    holonomic_drive_kinematics = new HolonomicDriveKinematics(
            holonomic_encoder_config, holonomic_wheel_locations
    );

    holonomic_drive_node = new HolonomicDriveNode(
            node_manager, "drivetrain", 
            primary_controller, inertial_sensor,
            holonomic_drive_motors, *holonomic_drive_kinematics
    );

    /* Define the intake components */
    intake_motor = new MotorNode(node_manager, 1, "intake", true);
    intake_motor_2 = new MotorNode(node_manager, 3, "intake2", true);
    intake_motor_3 = new MotorNode(node_manager, 4, "intake3", false);
    //indexer_motor = new MotorNode(node_manager, 6, "indexer", false);
    shooter_motor = new MotorNode(node_manager, 6, "shooter", true);
    shooter_motor_2 = new MotorNode(node_manager, 8, "shooter2", true);

    intake_node = new IntakeNode(node_manager, "intake", 
            primary_controller, pros::E_CONTROLLER_DIGITAL_A, 
            pros::E_CONTROLLER_DIGITAL_Y, {intake_motor, intake_motor_2, intake_motor_3}
    );	

    /*indexer_node = new IntakeNode(node_manager, "indexer", 
            primary_controller, pros::E_CONTROLLER_DIGITAL_R1, 
            pros::E_CONTROLLER_DIGITAL_R2, indexer_motor
    );*/	


    shooter_node = new ShooterNode(node_manager, "shooter", 
            primary_controller, pros::E_CONTROLLER_DIGITAL_R1, 
            {shooter_motor, shooter_motor_2}
    );

    //Create autonomous modes
    // OdomTest* odomTest = new OdomTest(holonomic_drive_node, odom_node, inertial_sensor);
    TestPathAuton* test_path = new TestPathAuton(holonomic_drive_node, odom_node);

    std::vector<Auton*> autons = {test_path};


    // Initialize the autonomous manager
	auton_manager_node = new AutonManagerNode(node_manager, autons);

    // Call the node manager to initialize all of the nodes above
    node_manager->initialize();

    // controller selection menus
    bool needsPath = selectAuton(primary_controller, auton_manager_node);
	pros::delay(500);
	if (needsPath) {
		selectPathJSON(primary_controller, auton_manager_node);
		pros::delay(500);
	}
	primary_controller->updateDisplay("Selection Complete");
}

void Robot15in::disabled() {}

void Robot15in::competition_initialize() {}

void Robot15in::autonomous() {node_manager->reset();

	// Reset the chosen autonomous and initialize
	auton_manager_node->selected_auton->AutonInit();
	
	// Execute autonomous code
	while (pros::competition::is_autonomous()) {
		node_manager->executeAuton();
        holonomic_drive_node->autonPeriodic();
        intake_node->autonPeriodic();
        indexer_node->autonPeriodic();
        shooter_node->autonPeriodic();
        encoder->autonPeriodic();
        inertial_sensor->autonPeriodic();
        odom_node ->autonPeriodic();
	}}

// Must put all telepPeriodic() method from each class into here
void Robot15in::opcontrol() {
    while (true) {
        // nodeManager->executeTeleop();
        holonomic_drive_node->teleopPeriodic();
        intake_node->teleopPeriodic();
        //indexer_node->teleopPeriodic();
        shooter_node->teleopPeriodic();
        encoder->teleopPeriodic();
        inertial_sensor->teleopPeriodic();
        odom_node->teleopPeriodic();
    }
}
