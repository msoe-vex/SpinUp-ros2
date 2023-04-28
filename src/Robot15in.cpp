#include "Robot15in.h"
#include "kinematics/TankDriveKinematics.h"
#include "nodes/subsystems/ButterflyNode.h"
#include "nodes/subsystems/TankDriveNode.h"
#include "pros/misc.h"

// Initializes 15in robot
void Robot15in::initialize() { 
    pros::lcd::initialize();
    node_manager = new NodeManager(pros::millis);
    primary_controller = new ControllerNode(node_manager, "primary");

    /* Define the drivetrain components */
    // For the 15in X-Drive `_2` motors are the ones on the top of the other motors
    left_front_drive = new MotorNode(node_manager, 2, "leftFrontDrive", true); // previously 16
    left_front_drive_2 = new MotorNode(node_manager, 1, "leftFrontTopDrive", true);
    left_rear_drive = new MotorNode(node_manager, 11, "leftRearDrive", true);
    left_rear_drive_2 = new MotorNode(node_manager, 12, "leftRearTopDrive", true);

    right_front_drive = new MotorNode(node_manager, 3, "rightFrontDrive", false);
    right_front_drive_2 = new MotorNode(node_manager, 4, "rightFrontTopDrive", false);
    right_rear_drive = new MotorNode(node_manager, 7, "rightRearDrive", false); // 2 is ded
    right_rear_drive_2 = new MotorNode(node_manager, 8, "rightRearTopDrive", false); // prev 3

    // Drive Node stuff
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

    // encoder = new ADIEncoderNode(node_manager, 'C', 'D', "encoder");        

    inertial_sensor = new InertialSensorNode(node_manager, "inertialSensor", 20); 

    holonomic_drive_kinematics = new HolonomicDriveKinematics(
            holonomic_encoder_config, holonomic_wheel_locations
    );

    holonomic_drive_node = new HolonomicDriveNode(
            node_manager, "drivetrain", 
            primary_controller, inertial_sensor,
            holonomic_drive_motors, *holonomic_drive_kinematics
    );

    //Manages switching drives for butterflyNode -- Is this button press->hold? --Andy Dao
    butterfly_node = new ButterflyNode(
        node_manager,
        "butterflyPistonNode",
        primary_controller,
        new ADIDigitalOutNode(node_manager, "butterflyNode", 'B', false), // initial state true for tank, false for holonomic
        pros::E_CONTROLLER_DIGITAL_Y,
        holonomic_drive_node
    );

    /* Define the intake components */
    intake_motor = new MotorNode(node_manager, 9, "intake", true);
    // intake_motor_2 = new MotorNode(node_manager, 3, "intake2", true);
    // intake_motor_3 = new MotorNode(node_manager, 4, "intake3", false);
    //indexer_motor = new MotorNode(node_manager, 6, "indexer", false);
    //shooter_motor = new MotorNode(node_manager, 6, "shooter", true);
    //shooter_motor_2 = new MotorNode(node_manager, 8, "shooter2", true);
    
    roller_motor = new MotorNode(node_manager, 20, "roller", true);

    intake_node = new IntakeNode(node_manager, "intake", 
            primary_controller, pros::E_CONTROLLER_DIGITAL_A, 
            pros::E_CONTROLLER_DIGITAL_R1, {intake_motor} //intake_motor_2, intake_motor_3}
    );

    roller_node = new RollerNode(node_manager, "rollerNode", primary_controller, pros::E_CONTROLLER_DIGITAL_L1, pros::E_CONTROLLER_DIGITAL_L2, {roller_motor});	

    /*
    shooter_piston_node = new ClawNode(
        node_manager,
        "shooterPistonNode",
        primary_controller,
        new ADIDigitalOutNode(node_manager, "shooterNode", 'H', false),
        pros::E_CONTROLLER_DIGITAL_R2
    ); */

    
    end_game_node = new ClawNode(
        node_manager,
        "endGameNode",
        primary_controller,
        new ADIDigitalOutNode(node_manager, "endGameNode", 'C', true),
        pros::E_CONTROLLER_DIGITAL_RIGHT
    );
    
    launcher_node = new LauncherNode(
        node_manager,
        "driveBaseNode",
        primary_controller,
        new ADIDigitalOutNode(node_manager, "driveBaseNode", 'A', false),
        new ADIDigitalOutNode(node_manager, "driveBaseNode", 'D', false),
        pros::E_CONTROLLER_DIGITAL_UP,
        pros::E_CONTROLLER_DIGITAL_R2
    );

    /*indexer_node = new IntakeNode(node_manager, "indexer", 
            primary_controller, pros::E_CONTROLLER_DIGITAL_R1, 
            pros::E_CONTROLLER_DIGITAL_R2, indexer_motor
    );*/	

    
    /*
    shooter_node = new ShooterNode(node_manager, "shooter", 
            primary_controller, pros::E_CONTROLLER_DIGITAL_R1, 
            {shooter_motor, shooter_motor_2}
    );	*/
    
    //drop_intake = new ADIDigitalOutNode(node_manager, "dropIntake", 'F', false);
}

void Robot15in::disabled() {}

void Robot15in::competition_initialize() {}

void Robot15in::autonomous() {
    // drop_intake->setValue(1);
    // holonomic_drive_node->setDriveVoltage(0, -MAX_MOTOR_VOLTAGE, 0);
    // pros::delay(500);
    // roller_node->setIntakeVoltage(MAX_MOTOR_VOLTAGE);
    // pros::delay(100);
    // roller_node->setIntakeVoltage(0);
    // holonomic_drive_node->setDriveVoltage(0, 0, 0);
}

// Must put all telepPeriodic() method from each class into here
void Robot15in::opcontrol() {
    while (true) {
        // nodeManager->executeTeleop();
        holonomic_drive_node->teleopPeriodic();
        intake_node->teleopPeriodic();
        //shooter_piston_node->teleopPeriodic();
        end_game_node->teleopPeriodic();
        butterfly_node->teleopPeriodic();
        launcher_node->teleopPeriodic();
        //indexer_node->teleopPeriodic();
        //shooter_node->teleopPeriodic();
        //encoder->teleopPeriodic();
        //inertial_sensor->teleopPeriodic();
        roller_node->teleopPeriodic();
    }
}
