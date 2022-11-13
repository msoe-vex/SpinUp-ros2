#include "main.h"
#include "nodes/actuator_nodes/MotorNode.h"
#include "nodes/subsystems/IntakeNode.h"

NodeManager *nodeManager;

NodeManager *node_manager = new NodeManager(pros::millis);

ControllerNode *primary_controller;

MotorNode *left_front_drive;
MotorNode *left_front_drive_2;
MotorNode *left_rear_drive;
MotorNode *left_rear_drive_2;
MotorNode *right_front_drive;
MotorNode *right_front_drive_2;
MotorNode *right_rear_drive;
MotorNode *right_rear_drive_2;
MotorNode *intake_motor;
MotorNode *shooter_motor;
MotorNode *shooter_motor_2;
MotorNode *indexer_motor;
HolonomicDriveNode *holonomic_drive_node;

ADIEncoderNode* encoder;

InertialSensorNode *inertial_sensor;

IntakeNode* intake_node;
IntakeNode *indexer_node;
ShooterNode* shooter_node;

// Initializes 15 in robot
void init15in() {
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
        360, // Ticks per RPM
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

    // TODO: PUT A GYRO ON THE ROBOT
    // Also put the right port here
    inertial_sensor =
        new InertialSensorNode(node_manager, "inertialSensor", 10); 

    HolonomicDriveKinematics holonomic_drive_kinematics(
        holonomic_encoder_config, holonomic_wheel_locations);

    holonomic_drive_node = new HolonomicDriveNode(
        node_manager, "drivetrain", primary_controller, inertial_sensor,
        holonomic_drive_motors, holonomic_drive_kinematics);

    /* Define the intake components */
    intake_motor = new MotorNode(node_manager, 5, "intake", true);
    indexer_motor = new MotorNode(node_manager, 7, "indexer", true);
    shooter_motor = new MotorNode(node_manager, 11, "shooter", true);
    shooter_motor_2 = new MotorNode(node_manager, 12, "shooter2", true);

    intake_node = new IntakeNode(node_manager, "intake", 
    primary_controller, pros::E_CONTROLLER_DIGITAL_R1, pros::E_CONTROLLER_DIGITAL_R2, intake_motor);	

    indexer_node = new IntakeNode(node_manager, "indexer", 
    primary_controller, pros::E_CONTROLLER_DIGITAL_X, pros::E_CONTROLLER_DIGITAL_Y, indexer_motor);	


    shooter_node = new ShooterNode(node_manager, "shooter", 
    primary_controller, pros::E_CONTROLLER_DIGITAL_L1, shooter_motor, shooter_motor_2);	
}

void init18in() {
    /* Define the drivetrain components */
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
        360, // Ticks per RPM
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

    // TODO: PUT A GYRO ON THE ROBOT
    // Also put the right port here
    inertial_sensor =
        new InertialSensorNode(node_manager, "inertialSensor", 10); 

    HolonomicDriveKinematics holonomic_drive_kinematics(
        holonomic_encoder_config, holonomic_wheel_locations);

    holonomic_drive_node = new HolonomicDriveNode(
        node_manager, "drivetrain", primary_controller, inertial_sensor,
        holonomic_drive_motors, holonomic_drive_kinematics);

    /* Define the intake components */
    intake_motor = new MotorNode(node_manager, 5, "intake", true);
    indexer_motor = new MotorNode(node_manager, 7, "indexer", true);
    shooter_motor = new MotorNode(node_manager, 11, "shooter", true);
    shooter_motor_2 = new MotorNode(node_manager, 12, "shooter2", true);

    intake_node = new IntakeNode(node_manager, "intake", 
    primary_controller, pros::E_CONTROLLER_DIGITAL_R1, pros::E_CONTROLLER_DIGITAL_R2, intake_motor);	

    indexer_node = new IntakeNode(node_manager, "indexer", 
    primary_controller, pros::E_CONTROLLER_DIGITAL_X, pros::E_CONTROLLER_DIGITAL_Y, indexer_motor);	

    shooter_node = new ShooterNode(node_manager, "shooter", 
    primary_controller, pros::E_CONTROLLER_DIGITAL_L1, shooter_motor, shooter_motor_2);	
}

// Default initialization if no robot name could be found
// Currently 15in
void initDefault() {
    init15in();
}

std::string getRobotName() {
    std::ifstream file("/usd/robotName.txt");

    if (file.is_open()) {
        std::string robotName;
        std::getline(file, robotName);
        file.close();
        return robotName;
    } else {
        return "Unknown";
    }
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize();
    nodeManager = new NodeManager(pros::millis);
    primary_controller = new ControllerNode(node_manager, "primary");

    // Maps robot name to initialization function
    // To add a new robot configuration...
    //      1. add the robot name as it appears in the robotName.txt file as the key
    //      2. add the initialization function for that robot as the value
    map<std::string, void (*)()> robotMap = {
        {"15in", init15in}, 
        {"18in", init18in}
    };

    // Selects which robot to initialize
    std::string robotName = getRobotName();
    if (robotMap.find(robotName) != robotMap.end()) {
        primary_controller->updateDisplay("Running " + robotName);
        robotMap[robotName]();
    } else {
        primary_controller->updateDisplay("Running Default");
        initDefault();
    }
    
    // Call the node manager to initialize all of the nodes above
    node_manager->initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // Reset all nodes to default configuration
  nodeManager->reset();

  // Execute teleop code
  while (true) {
    nodeManager->executeTeleop();
    holonomic_drive_node->teleopPeriodic();
    intake_node->teleopPeriodic();
    indexer_node->teleopPeriodic();
    shooter_node->teleopPeriodic();
    encoder->teleopPeriodic();
  }
}
