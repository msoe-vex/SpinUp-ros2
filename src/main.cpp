#include "main.h"
#include "nodes/actuator_nodes/MotorNode.h"
#include "nodes/subsystems/IntakeNode.h"
#include "RobotDefault.h"
#include "Robot15in.h"
#include "Robot18in.h"
#include "RobotKen.h"
#include "RobotFatAlbert.h"
#include "RobotBuddyBoiy.h"

// Below are the definitions for all the objects for both robots

NodeManager *node_manager = new NodeManager(pros::millis);

/* Robots */
IRobot* selectedRobot;
RobotDefault* robotDefault;
Robot15in* robot15in;
Robot18in* robot18in;
RobotKen* robotKen;
RobotFatAlbert* robotFatAlbert;
RobotBuddyBoiy* robotBuddyBoiy;

/* Maps robotNames to IRobots */
map<std::string, IRobot*> robotMap;

/* Name of the Robot */
std::string robotName;

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
    
    /* DO NO REMOVE THI DELAY OR EVERYTHING WILL BREAK */
    /* PLEASE FOR THE LOVE OF ALL THAT IS HOLY, KEEP THIS HERE */
    /* The LCD takes time to initialize and can cause weird issues if not given enough time to initialize */
    pros::delay(50);
    
    /* 
    To add a new robot configuration...
        1. Put a file in the top level folder on the SD Card called robotName.txt that 
        contains nothing but the name of the robot.
        2. Create a new subclass of IRobot.
        3. Define and initialize the new subclass in this file.
        4. Add a new <key, value> pair to the robotMap map below
            a. The key is the robot name as it appears in the robotName.txt file
            b. The value is the instance of the subclass of IRobot
    */

    /* Create Robot Objects */
    robotDefault = new RobotDefault;
    robot15in = new Robot15in;
    robot18in = new Robot18in;
    robotKen = new RobotKen;
    robotFatAlbert = new RobotFatAlbert;
    robotBuddyBoiy = new RobotBuddyBoiy;

    /* Maps robot name to initialization function */
    robotMap = {
        {"Default", robotDefault}
        {"15in", robot15in}, 
        {"18in", robot18in},
        {"Ken", robotKen},
        {"FatAlbert", robotFatAlbert},
        {"BuddyBoiy", robotBuddyBoiy},
    };

    /* Gets the name of the robot from the SD Card */
    robotName = getRobotName();

    // /* If the robot name can be found in the map, use it. If not, use default. */
    if (robotMap.find(robotName) != robotMap.end()) {
        selectedRobot = robotMap[robotName];
        // Using the overloaded version of updateDisplay() uses the C API that does not require an object
    } else {
        // use the default robot
        selectedRobot = robotMap.begin()->second;
    }

    selectedRobot->primary_controller->updateDisplay(pros::E_CONTROLLER_MASTER, "Running " + robotName);

    selectedRobot->initialize();
    
    // Call the node manager to initialize all of the nodes above
    // node_manager->initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
    selectedRobot->disabled();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
    selectedRobot->competition_initialize();
}

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
void autonomous() {
    selectedRobot->autonomous();
}

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
    // node_manager->reset();

    selectedRobot->opcontrol();
}
