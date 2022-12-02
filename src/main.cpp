#include "main.h"
#include "nodes/actuator_nodes/MotorNode.h"
#include "nodes/subsystems/IntakeNode.h"
#include "pros/rtos.h"

NodeManager *nodeManager;

NodeManager *node_manager = new NodeManager(pros::millis);

ControllerNode *primary_controller;

MotorNode *testingMotor;
MotorNode *testingMotorB;
ADIEncoderNode* encoder;


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize();

    nodeManager = new NodeManager(pros::millis);

    // Define all nodes used by the robot here
    primary_controller = new ControllerNode(node_manager, "primary");

    
    // for testing purposes a motor and encoder
    testingMotor = new MotorNode(node_manager, 12, "leftFrontDrive", true);
    testingMotorB = new MotorNode(node_manager, 11, "leftFrontDrive", true); // previously 16
    encoder = new ADIEncoderNode(node_manager, 'C', 'D', "encoder");        




    
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

    testingMotor->moveVelocity(40.0);
    testingMotor->moveVelocity(40.0);
    //float motorRPM = testingMotor->getRPM();
    float encoderRPM = encoder->getValue();
    //pros::lcd::print(0, std::to_string(motorRPM).c_str());
    pros::lcd::print(1, std::to_string(encoderRPM).c_str());
    //pros::lcd::clear();
    //pros::lcd::print(2, std::to_string(fabs(encoderRPM-motorRPM)/encoderRPM).c_str());
    
    pros::c::delay(10);

  }
}
