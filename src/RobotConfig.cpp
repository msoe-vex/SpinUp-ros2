#include "RobotConfig.h"

void RobotConfig::readConfig()
{
    std::ifstream file;
    file.open("/usd/robotConfig.txt");

    if (file.is_open())
    {
        for (int i = 0; i < 13; ++i)
        {
            configVector.push_back(std::make_pair(readPort(file), readReversed(file)));
        }
    }
    else
    {
        primary_controller->updateDisplay(pros::E_CONTROLLER_MASTER, "Error reading config");
    }
}

int RobotConfig::readPort(std::ifstream &file)
{
    std::string portString = "";
    std::getline(file, portString);
    return stoi(portString);
}

bool RobotConfig::readReversed(std::ifstream &file) {
    std::string reversedString = "";
    std::getline(file, reversedString);
    int reversedInt = stoi(reversedString);
    return reversedInt == 1;
}

// Initializes 18in robot
void RobotConfig::initialize()
{
    pros::lcd::initialize();
    node_manager = new NodeManager(pros::millis);
    primary_controller = new ControllerNode(node_manager, "primary");

    readConfig();

    /* Define the drivetrain components */
    left_drive_1 = new MotorNode(node_manager, configVector[0].first, "leftDrive1", configVector[0].second);
    left_drive_2 = new MotorNode(node_manager, configVector[1].first, "leftDrive2", configVector[1].second);
    left_drive_3 = new MotorNode(node_manager, configVector[2].first, "leftDrive3", configVector[2].second);
    left_drive_4 = new MotorNode(node_manager, configVector[3].first, "LeftDrive4", configVector[3].second);

    right_drive_1 = new MotorNode(node_manager, configVector[4].first, "rightDrive1", configVector[4].second);
    right_drive_2 = new MotorNode(node_manager, configVector[5].first, "rightDrive2", configVector[5].second);
    right_drive_3 = new MotorNode(node_manager, configVector[6].first, "rightRearDrive", configVector[6].second);
    right_drive_4 = new MotorNode(node_manager, configVector[7].first, "rightRearTopDrive", configVector[7].second);

    TankDriveNode::TankEightMotors tank_drive_motors = {
        left_drive_1, left_drive_2, left_drive_3, left_drive_4,
        right_drive_1, right_drive_2, right_drive_3, right_drive_4};

    TankDriveKinematics::TankWheelLocations tank_wheel_locations = {
        Vector2d(0, 0), // Left
        Vector2d(0, 0)  // Right
    };

    EncoderConfig encoder_config = {
        0,    // Initial ticks
        900., // Ticks per RPM
        3.25  // Wheel diameter
    };

    tank_kinematics = new TankDriveKinematics(encoder_config, tank_wheel_locations);

    tank_drive_node = new TankDriveNode(
        node_manager, "tankDrive", primary_controller,
        tank_drive_motors, *tank_kinematics);

    /* Define the intake components */
    intake_motor = new MotorNode(node_manager, configVector[8].first, "intake", configVector[8].second);
    indexer_motor = new MotorNode(node_manager, configVector[9].first, "indexer", configVector[9].second);

    intake_node = new IntakeNode(
        node_manager, "intake", primary_controller,
        pros::E_CONTROLLER_DIGITAL_A, pros::E_CONTROLLER_DIGITAL_B, {intake_motor});

    indexer_node = new IntakeNode(
        node_manager, "indexer", primary_controller,
        pros::E_CONTROLLER_DIGITAL_A, pros::E_CONTROLLER_DIGITAL_B, {indexer_motor});

    /* Define the Roller Components */
    roller_motor = new MotorNode(node_manager, configVector[10].first, "roller", configVector[10].second);

    roller_node = new IntakeNode(
        node_manager, "roller", primary_controller,
        pros::E_CONTROLLER_DIGITAL_L1, pros::E_CONTROLLER_DIGITAL_L2, {roller_motor});
    
    extra_motor_1 = new MotorNode(node_manager, configVector[11].first, "extra1", configVector[11].second);

    extra_node_1 = new IntakeNode(
        node_manager, "extra1", primary_controller,
        pros::E_CONTROLLER_DIGITAL_L1, pros::E_CONTROLLER_DIGITAL_L2, {extra_motor_1});
        
    extra_motor_2 = new MotorNode(node_manager, configVector[12].first, "extra2", configVector[12].second);

    extra_node_2 = new IntakeNode(
        node_manager, "extra2", primary_controller,
        pros::E_CONTROLLER_DIGITAL_X, pros::E_CONTROLLER_DIGITAL_Y, {extra_motor_2});
}

void RobotConfig::disabled() {}

void RobotConfig::competition_initialize() {}

void RobotConfig::autonomous() {}

// Must put all telepPeriodic() method from each class into here
void RobotConfig::opcontrol()
{
    while (true)
    {
        // nodeManager->executeTeleop();
        tank_drive_node->teleopPeriodic();
        intake_node->teleopPeriodic();
        indexer_node->teleopPeriodic();
        roller_node->teleopPeriodic();
        extra_node_1->teleopPeriodic();
        extra_node_2->teleopPeriodic();
    }
}
